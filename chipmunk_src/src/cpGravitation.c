/* Copyright (c) 2013 Scott Lembcke and Howling Moon Software
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "chipmunk/chipmunk_private.h"

static cpFloat
defaultGravitationForce(cpGravitation *gravity, cpFloat dist){
	cpBody *a = gravity->constraint.a;
	cpBody *b = gravity->constraint.b;
	return gravity->gravitationCoef*a->m*b->m/(float)(dist*dist);
}

static void
preStep(cpGravitation *gravity, cpFloat dt){}

static void applyCachedImpulse(cpGravitation *gravity, cpFloat dt_coef){}

static void
applyImpulse(cpGravitation *gravity, cpFloat dt)
{
	cpBody *a = gravity->constraint.a;
	cpBody *b = gravity->constraint.b;

	cpVect delta = cpvsub(a->p, b->p);
	cpFloat dist = cpvlength(delta);
	cpVect n = cpvmult(delta, 1.0f/(dist ? dist : INFINITY));

	cpFloat j = gravity->gravitationForceFunc((cpConstraint *)gravity, dist)*dt;
	gravity->jAcc = j;
	cpVect njAcc = cpvmult(n, j);

	// apply_impulses(a, b, gravity->r1, gravity->r2, njAcc);
	a->v = cpvadd(a->v, cpvmult(cpvneg(njAcc), a->m_inv));
	b->v = cpvadd(b->v, cpvmult(njAcc, b->m_inv));
}

static cpFloat
getImpulse(cpGravitation *gravity)
{
	return gravity->jAcc;
}

static const cpConstraintClass klass = {
	(cpConstraintPreStepImpl)preStep,
	(cpConstraintApplyCachedImpulseImpl)applyCachedImpulse,
	(cpConstraintApplyImpulseImpl)applyImpulse,
	(cpConstraintGetImpulseImpl)getImpulse,
};

cpGravitation *
cpGravitationAlloc(void)
{
	return (cpGravitation *)cpcalloc(1, sizeof(cpGravitation));
}

cpGravitation *
cpGravitationInit(cpGravitation *gravity, cpBody *a, cpBody *b, cpFloat gravitationCoef)
{
	cpConstraintInit((cpConstraint *)gravity, &klass, a, b);

	gravity->gravitationCoef = gravitationCoef;
	gravity->gravitationForceFunc = (cpGravitationForceFunc)defaultGravitationForce;

	gravity->jAcc = 0.0f;

	return gravity;
}

cpConstraint *
cpGravitationNew(cpBody *a, cpBody *b,  cpFloat gravitationCoef)
{
	return (cpConstraint *)cpGravitationInit(cpGravitationAlloc(), a, b,gravitationCoef);
}

cpBool
cpConstraintIsGravitation(const cpConstraint *constraint)
{
	return (constraint->klass == &klass);
}

cpFloat
cpGravitationGetGravitationConstant(const cpConstraint *constraint)
{
	cpAssertHard(cpConstraintIsGravitation(constraint), "Constraint is not a gravitation force.");
	return ((cpGravitation *)constraint)->gravitationCoef;
}

void
cpGravitationSetGravitationConstant(cpConstraint *constraint, cpFloat gravitationCoef)
{
	cpAssertHard(cpConstraintIsGravitation(constraint), "Constraint is not a gravitation force.");
	cpConstraintActivateBodies(constraint);
	((cpGravitation *)constraint)->gravitationCoef = gravitationCoef;
}

cpGravitationForceFunc
cpGravitationGetGravitationForceFunc(const cpConstraint *constraint)
{
	cpAssertHard(cpConstraintIsGravitation(constraint), "Constraint is not a gravitation force.");
	return ((cpGravitation *)constraint)->gravitationForceFunc;
}

void
cpGravitationSetGravitationForceFunc(cpConstraint *constraint, cpGravitationForceFunc gravitationForceFunc)
{
	cpAssertHard(cpConstraintIsGravitation(constraint), "Constraint is not a gravitation force.");
	cpConstraintActivateBodies(constraint);
	((cpGravitation *)constraint)->gravitationForceFunc = gravitationForceFunc;
}
