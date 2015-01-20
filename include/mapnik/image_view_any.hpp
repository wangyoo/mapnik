/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2014 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_IMAGE_VIEW_ANY_HPP
#define MAPNIK_IMAGE_VIEW_ANY_HPP

#include <mapnik/image_view.hpp>
#include <mapnik/util/variant.hpp>

namespace mapnik {

using image_view_base = util::variant<image_view_rgba8,
                                      image_view_gray8,
                                      image_view_gray16,
                                      image_view_gray32f>;

namespace detail {

struct get_view_width_visitor
{
    template <typename T>
    std::size_t operator()(T const& data) const
    {
        return data.width();
    }
};

struct get_view_height_visitor
{
    template <typename T>
    std::size_t operator()(T const& data) const
    {
        return data.height();
    }
};

struct get_view_size_visitor
{
    template <typename T>
    unsigned operator()(T const& data) const
    {
        return data.getSize();
    }
};

struct get_view_row_size_visitor
{
    template <typename T>
    unsigned operator()(T const& data) const
    {
        return data.getRowSize();
    }
};
} // namespace detail

struct image_view_any : image_view_base
{
    image_view_any() = default;

    template <typename T>
    image_view_any(T && data) noexcept
        : image_view_base(std::move(data)) {}

    std::size_t width() const
    {
        return util::apply_visitor(detail::get_view_width_visitor(),*this);
    }

    std::size_t height() const
    {
        return util::apply_visitor(detail::get_view_height_visitor(),*this);
    }

    unsigned getSize() const
    {
        return util::apply_visitor(detail::get_view_size_visitor(),*this);
    }

    unsigned getRowSize() const
    {
        return util::apply_visitor(detail::get_view_row_size_visitor(),*this);
    }
};

}

#endif // MAPNIK_IMAGE_VIEW_ANY_HPP
