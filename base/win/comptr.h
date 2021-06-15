// LAF Base Library
// Copyright (c) 2021 Igara Studio S.A.
// Copyright (c) 2017 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef BASE_WIN_COMPTR_H_INCLUDED
#define BASE_WIN_COMPTR_H_INCLUDED
#pragma once

#if !defined(_WIN32)
  #error This header file can be used only on Windows platform
#endif

#include <algorithm>

namespace base {

  template<class T>
  class ComPtr {
  public:
    ComPtr() : m_ptr(nullptr) {
    }

    ComPtr<T>(const ComPtr<T>& p) : m_ptr(p.m_ptr) {
      if (m_ptr)
        m_ptr->AddRef();
    }

    ComPtr(ComPtr&& tmp) {
      std::swap(m_ptr, tmp.m_ptr);
    }

    ~ComPtr() {
      reset();
    }

    T** operator&() { return &m_ptr; }
    T* operator->() { return m_ptr; }
    operator bool() const { return m_ptr != nullptr; }

    // Add new reference using operator=()
    ComPtr<T>& operator=(const ComPtr<T>& p) {
      if (m_ptr)
        m_ptr->Release();
      m_ptr = p.m_ptr;
      if (m_ptr)
        m_ptr->AddRef();
      return *this;
    }

    ComPtr& operator=(std::nullptr_t) {
      reset();
      return *this;
    }

    T* get() {
      return m_ptr;
    }

    void reset() {
      if (m_ptr) {
        m_ptr->Release();
        m_ptr = nullptr;
      }
    }

  private:
    T* m_ptr;
  };

} // namespace base

#endif
