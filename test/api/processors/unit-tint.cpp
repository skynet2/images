#include <catch2/catch_test_macros.hpp>

#include "../base.h"
#include "../max_color_distance.h"

#include <vips/vips8>

using vips::VImage;

TEST_CASE("tint", "[tint]") {
    SECTION("rgb image red") {
        auto test_image = fixtures->input_jpg;
        auto expected_image = fixtures->expected_dir + "/tint-red.jpg";
        auto params = "w=320&h=240&fit=cover&tint=FF0000";

        VImage image = process_file<VImage>(test_image, params);

        CHECK(image.width() == 320);
        CHECK(image.height() == 240);

        CHECK_THAT(image, is_max_color_distance(expected_image, 18));
    }

    SECTION("rgb image green") {
        auto test_image = fixtures->input_jpg;
        auto expected_image = fixtures->expected_dir + "/tint-green.jpg";
        auto params = "w=320&h=240&fit=cover&tint=00FF00";

        VImage image = process_file<VImage>(test_image, params);

        CHECK(image.width() == 320);
        CHECK(image.height() == 240);

        CHECK_THAT(image, is_max_color_distance(expected_image, 27));
    }

    SECTION("rgb image blue") {
        auto test_image = fixtures->input_jpg;
        auto expected_image = fixtures->expected_dir + "/tint-blue.jpg";
        auto params = "w=320&h=240&fit=cover&tint=0000FF";

        VImage image = process_file<VImage>(test_image, params);

        CHECK(image.width() == 320);
        CHECK(image.height() == 240);

        CHECK_THAT(image, is_max_color_distance(expected_image, 14));
    }

    SECTION("rgb image with sepia tone") {
        auto test_image = fixtures->input_jpg;
        auto expected_image = fixtures->expected_dir + "/tint-sepia.jpg";
        auto params = "w=320&h=240&fit=cover&tint=704214";

        VImage image = process_file<VImage>(test_image, params);

        CHECK(image.width() == 320);
        CHECK(image.height() == 240);

        CHECK_THAT(image, is_max_color_distance(expected_image, 10));
    }

    SECTION("rgb image with alpha channel") {
        auto test_image = fixtures->input_png_rgb_with_alpha;
        auto expected_image = fixtures->expected_dir + "/tint-alpha.png";
        auto params = "w=320&h=240&fit=cover&tint=704214";

        VImage image = process_file<VImage>(test_image, params);

        CHECK(image.width() == 320);
        CHECK(image.height() == 240);

        CHECK_THAT(image, is_max_color_distance(expected_image, 10));
    }

    SECTION("cmyk image red") {
        auto test_image = fixtures->input_jpg_with_cmyk_profile;
        auto expected_image = fixtures->expected_dir + "/tint-cmyk.jpg";
        auto params = "w=320&h=240&fit=cover&tint=FF0000";

        VImage image = process_file<VImage>(test_image, params);

        CHECK(image.width() == 320);
        CHECK(image.height() == 240);

        CHECK_THAT(image, is_max_color_distance(expected_image, 15));
    }
}
