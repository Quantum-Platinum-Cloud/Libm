/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*******************************************************************************
*                                                                              *
*     File:  llrint.c                                                          *
*                                                                              *
*     Contains: llrint{f} wrappers. 		       			       *
*                                                                              *
*     Copyright � 2001 Apple Computer, Inc.  All rights reserved.              *
*                                                                              *
*     Written by Stephen C. Peters, started in November 2001.                  *
*                                                                              *
*     A MathLib v5 file.                                                       *
*                                                                              *
*     Change History (most recent first):                                      *
*                                                                              *
*     08 Dec 01   scp   First created.                                         *
*                                                                              *
*     A version of gcc higher than 932 is required.                            *
*                                                                              *
*     GCC compiler options:                                                    *
*           optimization level 3 (-O3)                                         *
*           -fschedule-insns -finline-functions -funroll-all-loops             *
*                                                                              *
*******************************************************************************/
#include "math.h"
#include "fenv.h"
#include "limits.h"
#include "fp_private.h"

long long int llrint ( double x )
{
	double t;
	long long int result;
	fenv_t env;
	
	if (unlikely(x != x))
	{
		feraiseexcept(FE_INVALID);
		return LONG_LONG_MIN;
	}
	
	(void)fegetenv(&env);
	t = rint ( x );
	(void)fesetenv(&env);
	
	if ( t < (double)LONG_LONG_MIN )
	{
		feraiseexcept(FE_INVALID);
		result = LONG_LONG_MIN;
	}
	else if ( t > (double)LONG_LONG_MAX )
	{
		feraiseexcept(FE_INVALID);
		result = LONG_LONG_MAX;
	}
	else if (t != x)
	{
		feraiseexcept(FE_INEXACT);
		result = (long long int) t;
	}
	else
	{
		result = (long long int) t;
	}
	
    return result;
}

long long int llrintf (float x)
{
	float t;
	long long int result;
	fenv_t env;
	
	if (unlikely(x != x))
	{
		feraiseexcept(FE_INVALID);
		return LONG_LONG_MIN;
	}
	
	(void)fegetenv(&env);
	t = rintf ( x );
	(void)fesetenv(&env);
	
	if ( t < (float)LONG_LONG_MIN )
	{
		feraiseexcept(FE_INVALID);
		result = LONG_LONG_MIN;
	}
	else if ( t > (float)LONG_LONG_MAX )
	{
		feraiseexcept(FE_INVALID);
		result = LONG_LONG_MAX;
	}
	else if (t != x)
	{
		feraiseexcept(FE_INEXACT);
		result = (long long int) t;
	}
	else
	{
		result = (long long int) t;
	}
	
    return result;
}
