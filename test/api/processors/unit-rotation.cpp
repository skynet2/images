#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "../base.h"
#include "../similar_image.h"

#include <vips/vips8>

using Catch::Matchers::Equals;
using vips::VImage;

TEST_CASE("rotation", "[rotation]") {
    SECTION("by 30 degrees with semi-transparent background") {
        auto test_image = fixtures->input_jpg;
        auto expected_image =
            fixtures->expected_dir + "/rotate-transparent-bg.png";
        auto params = "w=320&ro=30&rbg=80FF0000";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("pngload_buffer"));

        CHECK(image.width() == 408);
        CHECK(image.height() == 386);

        CHECK_THAT(image, is_similar_image(expected_image));
    }

    SECTION("by 30 degrees with solid background") {
        auto test_image = fixtures->input_jpg;
        auto expected_image = fixtures->expected_dir + "/rotate-solid-bg.jpg";
        auto params = "w=320&ro=30&rbg=FF0000";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("jpegload_buffer"));

        CHECK(image.width() == 408);
        CHECK(image.height() == 386);

        CHECK_THAT(image, is_similar_image(expected_image));
    }

    SECTION("by 30 degrees, respecting output") {
        auto test_image = fixtures->input_jpg;
        auto params = "w=320&h=240&fit=cover&ro=30&output=jpg";

        VImage image = process_file<VImage>(test_image, params);

        CHECK_THAT(image.get_string("vips-loader"), Equals("jpegload_buffer"));

        CHECK(image.width() == 397);
        CHECK(image.height() == 368);
    }

    SECTION("by 30-multiple angle") {
        auto test_image = fixtures->input_jpg_320x240;

        std::vector<int> angles{-3750, -510, -150, 30, 390, 3630};

        for (const auto &angle : angles) {
            VImage image =
                process_file<VImage>(test_image, "ro=" + std::to_string(angle));

            CHECK(image.width() == 397);
            CHECK(image.height() == 368);
        }
    }

    SECTION("by 315 degrees, square output ignoring aspect ratio") {
        auto test_image = fixtures->input_jpg;
        auto params = "w=240&h=240&fit=fill&ro=315&output=jpg";

        VImage image = process_file<VImage>(test_image, params);

        CHECK(image.width() == 339);
        CHECK(image.height() == 339);
    }

    SECTION("by 30 degrees, rectangular output ignoring aspect ratio") {
        auto test_image = fixtures->input_jpg;
        auto params = "w=320&h=240&fit=fill&ro=30&output=jpg";

        VImage image = process_file<VImage>(test_image, params);

        CHECK(image.width() == 397);
        CHECK(image.height() == 368);
    }
}
