// Part of the Carbon Language project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef CARBON_TOOLCHAIN_CHECK_TYPE_COMPLETION_H_
#define CARBON_TOOLCHAIN_CHECK_TYPE_COMPLETION_H_

#include "toolchain/check/context.h"
#include "toolchain/check/diagnostic_helpers.h"
#include "toolchain/sem_ir/ids.h"

namespace Carbon::Check {

// Attempts to complete the type `type_id`. Returns `true` if the type is
// complete, or `false` if it could not be completed. A complete type has
// known object and value representations. Returns `true` if the type is
// symbolic.
//
// Avoid calling this where possible, as it can lead to coherence issues.
// However, it's important that we use it during monomorphization, where we
// don't want to trigger a request for more monomorphization.
// TODO: Remove the other call to this function.
auto TryToCompleteType(Context& context, SemIR::TypeId type_id, SemIRLoc loc,
                       Context::BuildDiagnosticFn diagnoser = nullptr) -> bool;

// Completes the type `type_id`. CHECK-fails if it can't be completed.
auto CompleteTypeOrCheckFail(Context& context, SemIR::TypeId type_id) -> void;

// Like `TryToCompleteType`, but for cases where it is an error for the type
// to be incomplete.
//
// If the type is not complete, `diagnoser` is invoked to diagnose the issue,
// if a `diagnoser` is provided. The builder it returns will be annotated to
// describe the reason why the type is not complete.
//
// `diagnoser` should build an error diagnostic. If `type_id` is dependent,
// the completeness of the type will be enforced during monomorphization, and
// `loc_id` is used as the location for a diagnostic produced at that time.
auto RequireCompleteType(Context& context, SemIR::TypeId type_id,
                         SemIR::LocId loc_id,
                         Context::BuildDiagnosticFn diagnoser) -> bool;

// Like `RequireCompleteType`, but also require the type to not be an abstract
// class type. If it is, `abstract_diagnoser` is used to diagnose the problem,
// and this function returns false.
auto RequireConcreteType(Context& context, SemIR::TypeId type_id,
                         SemIR::LocId loc_id,
                         Context::BuildDiagnosticFn diagnoser,
                         Context::BuildDiagnosticFn abstract_diagnoser) -> bool;

// Like `RequireCompleteType`, but also require the type to be defined. A
// defined type has known members. If the type is not defined, `diagnoser` is
// used to diagnose the problem, and this function returns false.
//
// This is the same as `RequireCompleteType` except for facet types, which are
// complete before they are fully defined.
auto RequireDefinedType(Context& context, SemIR::TypeId type_id,
                        SemIR::LocId loc_id,
                        Context::BuildDiagnosticFn diagnoser) -> bool;

// Returns the type `type_id` if it is a complete type, or produces an
// incomplete type error and returns an error type. This is a convenience
// wrapper around `RequireCompleteType`.
auto AsCompleteType(Context& context, SemIR::TypeId type_id,
                    SemIR::LocId loc_id, Context::BuildDiagnosticFn diagnoser)
    -> SemIR::TypeId;

// Returns the type `type_id` if it is a concrete type, or produces an
// incomplete or abstract type error and returns an error type. This is a
// convenience wrapper around `RequireConcreteType`.
auto AsConcreteType(Context& context, SemIR::TypeId type_id,
                    SemIR::LocId loc_id, Context::BuildDiagnosticFn diagnoser,
                    Context::BuildDiagnosticFn abstract_diagnoser)
    -> SemIR::TypeId;

}  // namespace Carbon::Check

#endif  // CARBON_TOOLCHAIN_CHECK_TYPE_COMPLETION_H_
