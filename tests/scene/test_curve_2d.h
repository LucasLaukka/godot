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

    CHECK_MESSAGE(
        curve->get_point_count() == 0,
        "Default Curve2D should contain the expected number of points.");
    CHECK_MESSAGE(
        curve->get_bake_interval() == 5,
        "Default Curve2D should contain the expected bake interval.");
}

TEST_CASE("[Curve2D] Modifying of curve") {
    Ref<Curve2D> curve = memnew(Curve2D);

    //Curve in the shape of a wave
    curve->add_point(Vector2(1,1), Vector2(0,0), Vector2(0,1));
    curve->add_point(Vector2(2,1), Vector2(0,1), Vector2(0,-1));
    curve->add_point(Vector2(3,1), Vector2(0,-1), Vector2(0,1));
    curve->add_point(Vector2(4,1), Vector2(0,1), Vector2(0,1));

    CHECK_MESSAGE(
        curve->get_point_count() == 4,
        "Curve2D should return the expected number of points.");

    CHECK_MESSAGE(
        curve->get_point_in(0) == Vector2(0,0),
        "Curve2D should return the expected control point in.");
    CHECK_MESSAGE(
        curve->get_point_out(0) == Vector2(0,1),
        "Curve2D should return the expected control point out.");
    CHECK_MESSAGE(
        curve->get_point_position(0) == Vector2(1,1), 
        "Curve2D should return the expected point position.");
    

    curve->set_point_in(1, Vector2(1,0));
    CHECK_MESSAGE(
        curve->get_point_in(1) == Vector2(1,0),
        "Curve2D should return the expected control point in after change.");
    
    curve->set_point_out(1, Vector2(0,1));
    CHECK_MESSAGE(
        curve->get_point_out(1) == Vector2(0,1),
         "Curve2D should return the expected control point out after change.");
       
    curve->remove_point(2);
    CHECK_MESSAGE(curve->get_point_count() == 3,
        "Curve2D should return the expected number of points after removing a point.");
    
    curve->set_point_count(5);
    CHECK_MESSAGE(curve->get_point_count() == 5,
        "Curve2D should return the expected number of points after setting the number of points.");

    curve->set_point_position(0, Vector2(1,1)); 
    CHECK_MESSAGE(
        curve->get_point_position(0) == Vector2(1,1),
        "Curve2D should return the correct point position after change.");

    curve->clear_points();
    CHECK_MESSAGE(
        curve->get_point_count() == 0,
        "Curve2D should return expected number of points after clear.");

}

TEST_CASE("[Curve2D] testing sampling of the curve"){
    Ref<Curve2D> curve = memnew(Curve2D);

    //Curve in the shape of a wave
    curve->add_point(Vector2(1,1), Vector2(0,0), Vector2(0,1));
    curve->add_point(Vector2(2,1), Vector2(0,1), Vector2(0,-1));
    curve->add_point(Vector2(3,1), Vector2(0,-1), Vector2(0,1));
    curve->add_point(Vector2(4,1), Vector2(0,1), Vector2(0,1));


    CHECK_MESSAGE(
        curve->sample(0, (real_t)0.5) == Vector2(1.5,1.75),
        "Curve2D should return the correct value");
    CHECK(curve->sample(1, (real_t)0.5) == Vector2(2.5, 0.25));
    CHECK(curve->sample(2, (real_t)0.5) == Vector2(3.5, 1.75));

    //samplef
    CHECK(curve->samplef((real_t) 0.25).is_equal_approx(Vector2(0.321, 0)));
    CHECK(curve->samplef((real_t) 0.25).x == doctest::Approx(curve->sample(0, (real_t) 0.25).x));
    CHECK(curve->samplef((real_t) 0.25).y == doctest::Approx(curve->sample(0, (real_t) 0.25).y));

    CHECK(curve->samplef((real_t) 1.1).x == doctest::Approx(curve->sample(1, (real_t)0.1).x));
    CHECK(curve->samplef((real_t) 1.1).y == doctest::Approx(curve->sample(1, (real_t)0.1).y));

    CHECK(curve->samplef((real_t) 2.9).x == doctest::Approx(curve->sample(2, (real_t)0.9).x));
    CHECK(curve->samplef((real_t) 2.9).y == doctest::Approx(curve->sample(2, (real_t)0.9).y));

    CHECK(curve->samplef((real_t) 3.01) == Vector2(4,1));


    //get_closest_offset
   // CHECK(curve->get_glosest_offset(Vector2(3,1)) == (real_t) 0);

}

TEST_CASE("[Curve2D] testing baked points in curve"){

    Ref<Curve2D> curve = memnew(Curve2D);
    
    curve->add_point(Vector2(1,1), Vector2(0,0), Vector2(0,1));
    curve->add_point(Vector2(2,1), Vector2(0,1), Vector2(0,-1));
    curve->add_point(Vector2(3,1), Vector2(0,-1), Vector2(0,1));
    curve->add_point(Vector2(4,1), Vector2(0,1), Vector2(0,1));
    
    PackedVector2Array p2a{};
    p2a.append(Vector2(1,1));
    p2a.append(Vector2(2,1));
    p2a.append(Vector2(3,1));
    p2a.append(Vector2(4,1));

    CHECK(curve->get_baked_points() == p2a);
    curve->set_bake_interval(4);
    CHECK(curve->get_bake_interval() == 4);
    curve->set_bake_interval(5);

    //sample baked
    CHECK(curve->sample_baked(curve->get_closest_offset(Vector2(1.5,1))) == Vector2(2,1));


    Transform2D tf2d{};
    //sample_baked_with_rotation
    //CHECK(curve->sample_baked_with_rotation((real_t)0.1, true, false, (real_t) 0.1) == tf2d);

}

TEST_CASE("[Curve2D] testing tesselation"){
    
    Ref<Curve2D> curve = memnew(Curve2D);
    
    curve->add_point(Vector2(1,1), Vector2(0,0), Vector2(0,1));
    curve->add_point(Vector2(2,1), Vector2(0,1), Vector2(0,-1));
    curve->add_point(Vector2(3,1), Vector2(0,-1), Vector2(0,1));
    curve->add_point(Vector2(4,1), Vector2(0,1), Vector2(0,1));

    Vector2 p(1.4, 1);
    Vector2 p2(1.6, 1);

    //get_closest_point
    //CHECK(curve->get_closest_point(p) == Vector2(1,1));
    //CHECK(curve->get_closest_point(p2) == Vector2(2,1));


    //tessellate
   /* PackedVector2Array p2a{} = curve->tesselate();
    for(int i = 0; i < p2a.size(); i++)
    {
        CHECK(p2a[i].x >= 1 && p2a[i] <= 4); 
        CHECK(p2a[i].y >= 0 && p2a[i].y <= 2);   
    }*/
}

} //namespace TestCurve2D

#endif // TEST_CURVE_2D_H