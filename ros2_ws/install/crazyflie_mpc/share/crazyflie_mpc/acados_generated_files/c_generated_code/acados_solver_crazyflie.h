/*
 * Copyright (c) The acados authors.
 *
 * This file is part of acados.
 *
 * The 2-Clause BSD License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.;
 */

#ifndef ACADOS_SOLVER_crazyflie_H_
#define ACADOS_SOLVER_crazyflie_H_

#include "acados/utils/types.h"

#include "acados_c/ocp_nlp_interface.h"
#include "acados_c/external_function_interface.h"

#define CRAZYFLIE_NX     9
#define CRAZYFLIE_NZ     0
#define CRAZYFLIE_NU     4
#define CRAZYFLIE_NP     0
#define CRAZYFLIE_NBX    9
#define CRAZYFLIE_NBX0   9
#define CRAZYFLIE_NBU    4
#define CRAZYFLIE_NSBX   0
#define CRAZYFLIE_NSBU   0
#define CRAZYFLIE_NSH    0
#define CRAZYFLIE_NSH0   0
#define CRAZYFLIE_NSG    0
#define CRAZYFLIE_NSPHI  0
#define CRAZYFLIE_NSHN   0
#define CRAZYFLIE_NSGN   0
#define CRAZYFLIE_NSPHIN 0
#define CRAZYFLIE_NSPHI0 0
#define CRAZYFLIE_NSBXN  0
#define CRAZYFLIE_NS     0
#define CRAZYFLIE_NS0    0
#define CRAZYFLIE_NSN    0
#define CRAZYFLIE_NG     0
#define CRAZYFLIE_NBXN   0
#define CRAZYFLIE_NGN    0
#define CRAZYFLIE_NY0    13
#define CRAZYFLIE_NY     13
#define CRAZYFLIE_NYN    9
#define CRAZYFLIE_N      50
#define CRAZYFLIE_NH     0
#define CRAZYFLIE_NHN    0
#define CRAZYFLIE_NH0    0
#define CRAZYFLIE_NPHI0  0
#define CRAZYFLIE_NPHI   0
#define CRAZYFLIE_NPHIN  0
#define CRAZYFLIE_NR     0

#ifdef __cplusplus
extern "C" {
#endif


// ** capsule for solver data **
typedef struct crazyflie_solver_capsule
{
    // acados objects
    ocp_nlp_in *nlp_in;
    ocp_nlp_out *nlp_out;
    ocp_nlp_out *sens_out;
    ocp_nlp_solver *nlp_solver;
    void *nlp_opts;
    ocp_nlp_plan_t *nlp_solver_plan;
    ocp_nlp_config *nlp_config;
    ocp_nlp_dims *nlp_dims;

    // number of expected runtime parameters
    unsigned int nlp_np;

    /* external functions */
    // dynamics

    external_function_param_casadi *forw_vde_casadi;
    external_function_param_casadi *expl_ode_fun;




    // cost






    // constraints







} crazyflie_solver_capsule;

ACADOS_SYMBOL_EXPORT crazyflie_solver_capsule * crazyflie_acados_create_capsule(void);
ACADOS_SYMBOL_EXPORT int crazyflie_acados_free_capsule(crazyflie_solver_capsule *capsule);

ACADOS_SYMBOL_EXPORT int crazyflie_acados_create(crazyflie_solver_capsule * capsule);

ACADOS_SYMBOL_EXPORT int crazyflie_acados_reset(crazyflie_solver_capsule* capsule, int reset_qp_solver_mem);

/**
 * Generic version of crazyflie_acados_create which allows to use a different number of shooting intervals than
 * the number used for code generation. If new_time_steps=NULL and n_time_steps matches the number used for code
 * generation, the time-steps from code generation is used.
 */
ACADOS_SYMBOL_EXPORT int crazyflie_acados_create_with_discretization(crazyflie_solver_capsule * capsule, int n_time_steps, double* new_time_steps);
/**
 * Update the time step vector. Number N must be identical to the currently set number of shooting nodes in the
 * nlp_solver_plan. Returns 0 if no error occurred and a otherwise a value other than 0.
 */
ACADOS_SYMBOL_EXPORT int crazyflie_acados_update_time_steps(crazyflie_solver_capsule * capsule, int N, double* new_time_steps);
/**
 * This function is used for updating an already initialized solver with a different number of qp_cond_N.
 */
ACADOS_SYMBOL_EXPORT int crazyflie_acados_update_qp_solver_cond_N(crazyflie_solver_capsule * capsule, int qp_solver_cond_N);
ACADOS_SYMBOL_EXPORT int crazyflie_acados_update_params(crazyflie_solver_capsule * capsule, int stage, double *value, int np);
ACADOS_SYMBOL_EXPORT int crazyflie_acados_update_params_sparse(crazyflie_solver_capsule * capsule, int stage, int *idx, double *p, int n_update);

ACADOS_SYMBOL_EXPORT int crazyflie_acados_solve(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT void crazyflie_acados_batch_solve(crazyflie_solver_capsule ** capsules, int N_batch);
ACADOS_SYMBOL_EXPORT int crazyflie_acados_free(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT void crazyflie_acados_print_stats(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT int crazyflie_acados_custom_update(crazyflie_solver_capsule* capsule, double* data, int data_len);


ACADOS_SYMBOL_EXPORT ocp_nlp_in *crazyflie_acados_get_nlp_in(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT ocp_nlp_out *crazyflie_acados_get_nlp_out(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT ocp_nlp_out *crazyflie_acados_get_sens_out(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT ocp_nlp_solver *crazyflie_acados_get_nlp_solver(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT ocp_nlp_config *crazyflie_acados_get_nlp_config(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT void *crazyflie_acados_get_nlp_opts(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT ocp_nlp_dims *crazyflie_acados_get_nlp_dims(crazyflie_solver_capsule * capsule);
ACADOS_SYMBOL_EXPORT ocp_nlp_plan_t *crazyflie_acados_get_nlp_plan(crazyflie_solver_capsule * capsule);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // ACADOS_SOLVER_crazyflie_H_
