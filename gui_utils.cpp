#include "gui_utils.hpp"

namespace def
{
    bool IsPointInRect(const Vector2i& point, const Vector2i& rect_pos, const Vector2i& rect_size)
    {
        return point >= rect_pos && point < rect_pos + rect_size;
    }
}
