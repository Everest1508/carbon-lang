// Part of the Carbon Language project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
// NOAUTOUPDATE

package ExplorerTest api;

fn id[T:! type](x: i32) -> i32 {
  return x;
}

fn Main() -> i32 {
  // CHECK:STDERR: COMPILATION ERROR: fail_type_deduction_unused.carbon:[[@LINE+1]]: could not deduce type argument for type parameter T in call
  return id(0);
}
