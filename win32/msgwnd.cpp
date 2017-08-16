/* win32/msgwnd.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "win32/msgwnd.hpp"
#include "win32/synch.hpp"
#include "win32/uuid.hpp"
#include "util/memory.hpp"
#include "util/methodscope.hpp"

using namespace Windows;

MsgWnd::MsgWnd(HINSTANCE hInstance, std::function< void (UINT, WPARAM, LPARAM) > f) :
  _closing(false),
  _hInstance(hInstance),
  _f(f),
  _hWnd(NULL),
  _lastError(0)
{

}

MsgWnd::~MsgWnd()
{
  doClose(false);
}

HWND MsgWnd::handle() const
{
  return _hWnd;
}

void MsgWnd::start()
{
  Synch::Semaphore sem(0,1);

  _t.reset(new Thread([this, &sem] ()
    {
      WNDCLASSEX wx;

      std::wstring uuidStr(Uuid().value());

      clearMem(wx);
      wx.cbSize = sizeof(WNDCLASSEX);
      wx.lpfnWndProc = wndProc;
      wx.lpszClassName = uuidStr.c_str();
      wx.hInstance = _hInstance;

      {
        MethodScope semScope([&sem] () { sem.release(); } );

        if (!RegisterClassEx(&wx))
          throw Exception();
  
        if ((_hWnd = CreateWindowEx(0,uuidStr.c_str(),NULL,0,0,0,0,0,HWND_MESSAGE,NULL,_hInstance,
                                    reinterpret_cast< LPVOID >(this))) == NULL)
          throw Exception();
      }

      MethodScope classScope([this, uuidStr] () { UnregisterClass(uuidStr.c_str(),_hInstance); });

      if (_hWnd)
      {
        MSG msg;
        BOOL bRet;

        while ((bRet = GetMessage(&msg,NULL,0,0)) != 0)
        {
          if (bRet == -1)
            throw Exception();
          else
          {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
          }
        }
      }
    }));

  sem.acquire();
}

void MsgWnd::doClose(bool rethrow)
{
  if (!_t)
    return;

  try
  {
    _closing = true;
    if (!PostMessage(handle(),WM_CLOSE,0,0))
      throw Exception();

    _t->join();
    _t.reset();

    if (_lastError)
      throw Exception();
  }
  catch (...)
  {
    _t.reset();

    if (rethrow)
      throw;
  }
}

void MsgWnd::close()
{
  doClose(true);
}

LRESULT CALLBACK MsgWnd::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_NCCREATE:
      {
        SetLastError(0);
        LONG_PTR wndPtr = reinterpret_cast< LONG_PTR >(reinterpret_cast< LPCREATESTRUCT >(lParam)->lpCreateParams);
        MsgWnd *me = reinterpret_cast< MsgWnd * >(wndPtr);
        SetWindowLongPtr(hWnd,GWLP_USERDATA,wndPtr);
        if (GetLastError() && me && !me->_lastError)
          me->_lastError = GetLastError();
      }
      return TRUE;

    case WM_CREATE:
    case WM_NCCALCSIZE:
    case WM_GETMINMAXINFO:
    case WM_NCDESTROY:
      return DefWindowProc(hWnd,uMsg,wParam,lParam);

    case WM_CLOSE:
      {
        MsgWnd *me = reinterpret_cast< MsgWnd * >(GetWindowLongPtr(hWnd,GWLP_USERDATA));

        if (me && me->_closing)
        {
          if (!DestroyWindow(hWnd))
          {
            if (!me->_lastError)
              me->_lastError = GetLastError();
          }

          return FALSE;
        }
      }
      return TRUE;

    case WM_DESTROY:
      {
        MsgWnd *me = reinterpret_cast< MsgWnd * >(GetWindowLongPtr(hWnd,GWLP_USERDATA));

        if (me && me->_closing)
        {
          PostQuitMessage(0);
          return FALSE;
        }
      }
      return TRUE;

    default:
      {
        MsgWnd *me = reinterpret_cast< MsgWnd * >(GetWindowLongPtr(hWnd,GWLP_USERDATA));

        if (me && !me->_closing)
          me->_f(uMsg,wParam,lParam);
      }
      return FALSE;
  }
}
