/*
 * Copyright (C) 2024 The Geeqie Team
 *
 * Author: Omari Stephens
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *
 * Unit tests for pixbuf-util.cc
 *
 */

#include "gtest/gtest.h"

#include "pixbuf-util.h"
#include <cstring>

namespace {

TEST(PixbufUtilTest, SetRectFillFillsPixels)
{
        constexpr gint w = 4;
        constexpr gint h = 4;
        GdkPixbuf *pb = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, w, h);
        const gint stride = gdk_pixbuf_get_rowstride(pb);
        std::memset(gdk_pixbuf_get_pixels(pb), 0, stride * h);

        pixbuf_set_rect_fill(pb, 1, 1, 2, 2, 10, 20, 30, 40);

        guchar *pix = gdk_pixbuf_get_pixels(pb);
        for (gint y = 1; y < 3; y++)
                {
                for (gint x = 1; x < 3; x++)
                        {
                        guchar *p = pix + y * stride + x * 4;
                        EXPECT_EQ(10, p[0]);
                        EXPECT_EQ(20, p[1]);
                        EXPECT_EQ(30, p[2]);
                        EXPECT_EQ(40, p[3]);
                        }
                }

        g_object_unref(pb);
}

TEST(PixbufUtilTest, PixelSetSetsPixel)
{
        GdkPixbuf *pb = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 2, 2);
        const gint stride = gdk_pixbuf_get_rowstride(pb);
        std::memset(gdk_pixbuf_get_pixels(pb), 0, stride * 2);

        pixbuf_pixel_set(pb, 1, 0, 11, 22, 33, 44);

        guchar *pix = gdk_pixbuf_get_pixels(pb);
        guchar *p = pix + 0 * stride + 1 * 4;
        EXPECT_EQ(11, p[0]);
        EXPECT_EQ(22, p[1]);
        EXPECT_EQ(33, p[2]);
        EXPECT_EQ(44, p[3]);

        g_object_unref(pb);
}

}  // anonymous namespace

/* vim: set shiftwidth=8 softtabstop=0 cindent cinoptions={1s: */
