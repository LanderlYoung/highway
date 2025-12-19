// Copyright 2022 Google LLC
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Enable all targets so that calling Have* does not call into a null pointer.
#ifndef HWY_COMPILE_ALL_ATTAINABLE
#define HWY_COMPILE_ALL_ATTAINABLE
#endif
#include "hwy/per_target.h"

#include <stddef.h>
#include <stdint.h>

#undef HWY_TARGET_INCLUDE
#define HWY_TARGET_INCLUDE "hwy/per_target.cc"
#include "hwy/foreach_target.h"  // IWYU pragma: keep
#include "hwy/highway.h"

HWY_BEFORE_NAMESPACE();
namespace hwy {
namespace detail {
namespace HWY_NAMESPACE {
HWY_HEADER_ONLY_FUN
int64_t GetTarget() { return HWY_TARGET; }
HWY_HEADER_ONLY_FUN
size_t GetVectorBytes() {
  namespace hn = ::hwy::HWY_NAMESPACE;
  return hn::Lanes(hn::ScalableTag<uint8_t>());
}
HWY_HEADER_ONLY_FUN
bool GetHaveInteger64() { return HWY_HAVE_INTEGER64 != 0; }
HWY_HEADER_ONLY_FUN
bool GetHaveFloat16() { return HWY_HAVE_FLOAT16 != 0; }
HWY_HEADER_ONLY_FUN
bool GetHaveFloat64() { return HWY_HAVE_FLOAT64 != 0; }
// NOLINTNEXTLINE(google-readability-namespace-comments)
}  // namespace HWY_NAMESPACE
}  // namespace detail
}  // namespace hwy
HWY_AFTER_NAMESPACE();

#if HWY_ONCE
namespace hwy {
namespace detail {
HWY_HEADER_ONLY_FUN
int64_t DispatchedTargetHelper() {
  HWY_EXPORT(GetTarget);
  return HWY_DYNAMIC_DISPATCH(GetTarget)();
}

HWY_HEADER_ONLY_FUN
size_t VectorBytesHelper() {
  HWY_EXPORT(GetVectorBytes);
  return HWY_DYNAMIC_DISPATCH(GetVectorBytes)();
}

HWY_HEADER_ONLY_FUN
bool HaveInteger64Helper() {
  HWY_EXPORT(GetHaveInteger64);
  return HWY_DYNAMIC_DISPATCH(GetHaveInteger64)();
}

HWY_HEADER_ONLY_FUN
bool HaveFloat16Helper() {
  HWY_EXPORT(GetHaveFloat16);
  return HWY_DYNAMIC_DISPATCH(GetHaveFloat16)();
}

HWY_HEADER_ONLY_FUN
bool HaveFloat64Helper() {
  HWY_EXPORT(GetHaveFloat64);
  return HWY_DYNAMIC_DISPATCH(GetHaveFloat64)();
}
}

HWY_HEADER_ONLY_FUN
HWY_DLLEXPORT int64_t DispatchedTarget() {
  return detail::DispatchedTargetHelper();
}

HWY_HEADER_ONLY_FUN
HWY_DLLEXPORT size_t VectorBytes() {
  return detail::VectorBytesHelper();
}

HWY_HEADER_ONLY_FUN
HWY_DLLEXPORT bool HaveInteger64() {
  return detail::HaveInteger64Helper();
}

HWY_HEADER_ONLY_FUN
HWY_DLLEXPORT bool HaveFloat16() {
  return detail::HaveFloat16Helper();
}

HWY_HEADER_ONLY_FUN
HWY_DLLEXPORT bool HaveFloat64() {
  return detail::HaveFloat64Helper();
}

}  // namespace hwy
#endif  // HWY_ONCE
