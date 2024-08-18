#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "../base.h"
#include "../max_color_distance.h"
#include "../similar_image.h"

#include <vips/vips8>

using Catch::Matchers::Equals;
using vips::VImage;

TEST_CASE("flatten", "[background]") {
    SECTION("to white") {
        auto test_image = fixtures->input_png_with_transparency;
        auto expected_image = fixtures->expected_dir + "/flatten-white.png";
        auto params = "w=400&h=300&fit=cover&bg=white";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("pngload_buffer"));

        CHECK(image.width() == 400);
        CHECK(image.height() == 300);

        CHECK_THAT(image, is_similar_image(expected_image));
    }

    SECTION("to orange") {
        auto test_image = fixtures->input_png_with_transparency;
        auto expected_image = fixtures->expected_dir + "/flatten-orange.png";
        auto params = "w=400&h=300&fit=cover&bg=darkorange";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("pngload_buffer"));

        CHECK(image.width() == 400);
        CHECK(image.height() == 300);

        CHECK_THAT(image, is_similar_image(expected_image));
    }

    SECTION("to hex") {
        auto test_image = fixtures->input_png_with_transparency;
        auto expected_image = fixtures->expected_dir + "/flatten-orange.png";
        auto params = "w=400&h=300&fit=cover&bg=FF8C00";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("pngload_buffer"));

        CHECK(image.width() == 400);
        CHECK(image.height() == 300);

        CHECK_THAT(image, is_similar_image(expected_image));
    }

    SECTION("16bit with transparency to orange") {
        auto test_image = fixtures->input_png_with_transparency_16bit;
        auto expected_image =
            fixtures->expected_dir + "/flatten-rgb16-orange.png";
        auto params = "bg=darkorange";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("pngload_buffer"));

        CHECK(image.width() == 32);
        CHECK(image.height() == 32);

        CHECK_THAT(image, is_max_color_distance(expected_image));
    }

    SECTION("greyscale to orange") {
        auto test_image = fixtures->input_png_with_grey_alpha;
        auto expected_image = fixtures->expected_dir + "/flatten-2channel.png";
        auto params = "w=320&h=240&fit=cover&filt=greyscale&bg=darkorange";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("pngload_buffer"));

        CHECK(image.bands() == 1);
        CHECK(image.width() == 320);
        CHECK(image.height() == 240);

        CHECK_THAT(image, is_similar_image(expected_image));
    }

    SECTION("blur to orange should unpremultiply") {
        auto test_image = fixtures->input_png_with_transparency;
        auto expected_image =
            fixtures->expected_dir + "/flatten-blur-orange.png";
        auto params = "w=400&h=300&fit=cover&blur=1&bg=darkorange";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("pngload_buffer"));

        CHECK(image.width() == 400);
        CHECK(image.height() == 300);

        CHECK_THAT(image, is_similar_image(expected_image));
    }
}

TEST_CASE("composite to 50% orange", "[background]") {
    auto test_image = fixtures->input_png_with_transparency;
    auto expected_image = fixtures->expected_dir + "/composite-50-orange.png";
    auto params = "w=400&h=300&fit=cover&bg=80FF8C00";

    VImage image = process_file<VImage>(test_image, params);

    CHECK_THAT(image.get_string("vips-loader"), Equals("pngload_buffer"));

    CHECK(image.width() == 400);
    CHECK(image.height() == 300);

    CHECK_THAT(image, is_similar_image(expected_image));
}

TEST_CASE("ignore", "[background]") {
    SECTION("for jpeg") {
        auto test_image = fixtures->input_jpg;
        auto params = "bg=FF0000";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("jpegload_buffer"));

        CHECK(image.bands() == 3);
    }

    SECTION("for transparent background") {
        auto test_image = fixtures->input_png_with_transparency;
        auto params = "bg=0FFF";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("pngload_buffer"));

        CHECK(image.bands() == 4);
    }
}
