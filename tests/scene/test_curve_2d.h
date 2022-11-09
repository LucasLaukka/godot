/*************************************************************************/
/*  test_curve_2d.h                                                         */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef TEST_CURVE_2D_H
#define TEST_CURVE_2D_H

#include "tests/test_macros.h"
#include "scene/resources/curve.h"

namespace TestCurve2D {

TEST_CASE("[Curve2D] Default curve2D") {
	const Ref<Curve2D> curve = memnew(Curve2D);
    CHECK(curve->get_point_count() == 0);
   
}

TEST_CASE("[Curve2D] Modifying Custom curve2D") {
	
    Ref<Curve2D> curve = memnew(Curve2D);

    curve->add_point(Vector2(0,0));
    curve->add_point(Vector2(0.25, 1));
	curve->add_point(Vector2(0.5, 0));
	curve->add_point(Vector2(0.75, 1));

    CHECK(curve->get_point_count() == 4);

    CHECK(curve->get_point_in(0) == Vector2(0,0));
    CHECK(curve->get_point_out(0) == Vector2(0,0));
    
    curve->set_point_in(1, Vector2(1,0));
    curve->set_point_out(1, Vector2(0,1));

    CHECK(curve->get_point_in(1) == Vector2(1,0));
    CHECK(curve->get_point_out(1) == Vector2(0,1));

    CHECK(Math::is_zero_approx(curve->sample(0,0).x));
    CHECK(Math::is_zero_approx(curve->sample(0,0).y));
    
    curve->remove_point(2);
    CHECK(curve->get_point_count() == 3);

    curve->set_point_count(5);
    CHECK(curve->get_point_count() == 5);

    curve->set_point_position(0, Vector2(1,1));
    CHECK(curve->get_point_position(0) == Vector2(1,1));

    curve->clear_points();

    CHECK(curve->get_point_count() == 0);

}

TEST_CASE("[Curve2D] ..."){
    //sample

    Ref<Curve2D> curve = memnew(Curve2D);

    curve->add_point(Vector2(0,0.1));
    curve->add_point(Vector2(0.25, 1));
	curve->add_point(Vector2(0.5, 0));
	curve->add_point(Vector2(0.75, 1));

    CHECK(curve->sample(0, 0.1) == Vector2());
    //CHECK(curve->sample(1, 0.1) == doctest::Approx((real_t)0.352));

    //samplef

    //sample_baked_with_rotation

    //get_baked_points

    //set_bake_interval

    //get_bake_interval

    //get_closest_point

    //get_closest_offset

    //tessellate


}

} //namespace TestCurve2D

#endif // TEST_CURVE_2D_H