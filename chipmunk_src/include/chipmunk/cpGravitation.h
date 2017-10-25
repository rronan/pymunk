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

/// @defgroup cpGravitation cpGravitation
/// @{

/// Check if a constraint is a slide joint.
CP_EXPORT cpBool cpConstraintIsGravitation(const cpConstraint *constraint);

/// Function type used for gravity force force callbacks.
typedef cpFloat (*cpGravitationForceFunc)(cpConstraint *gravity, cpFloat dist);

/// Allocate a gravity force.
CP_EXPORT cpGravitation* cpGravitationAlloc(void);
/// Initialize a gravity force.
CP_EXPORT cpGravitation* cpGravitationInit(cpGravitation *joint, cpBody *a, cpBody *b, cpFloat gravitationCoef);
/// Allocate and initialize a gravity force.
CP_EXPORT cpConstraint* cpGravitationNew(cpBody *a, cpBody *b, cpFloat gravitationCoef);

/// Get the gravitational constant.
CP_EXPORT cpFloat cpGravitationGetGravitationCoef(const cpConstraint *constraint);
/// Set the gravitational constant.
CP_EXPORT void cpGravitationSetGravitationCoef(cpConstraint *constraint, cpFloat gravitationCoef);

/// Get the force.
CP_EXPORT cpGravitationForceFunc cpGravitationGetGravitationForceFunc(const cpConstraint *constraint);
/// Set the force.
CP_EXPORT void cpGravitationSetGravitationForceFunc(cpConstraint *constraint, cpGravitationForceFunc gravitationForceFunc);

/// @}
