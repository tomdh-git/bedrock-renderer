#pragma once
#include "client/features/render/Fonts.h"

// Lucide icons (ISC licence, https://lucide.dev) as a font: resources/fonts/Lucide-Icons.ttf is the upstream icon font cut down to the glyphs the client uses
// (about 5 KB). A glyph is rasterised by the font engine at the exact pixel size it is drawn at, the way text is, so it stays sharp at every size instead of
// being a stroked path whose edges land between pixels. Every glyph fills the font's 1000 x 1000 em box (Lucide's 24 x 24 viewBox), ascent 1000 and descent 0, so
// one `size` means the same optical box everywhere (dock tiles, bottom-bar discs, cards).
//
// To add an icon: add its codepoint to the subset (pyftsubset over lucide-static's font/lucide.ttf, codepoints in lucide.css), one value in `Icon`, one `case`
// in `codepoint`.
namespace Render {

struct icons {
    enum class Icon { Play, Settings, Users, FileText, Image, Search, Plus, MessageCircle, User, ArrowLeftRight, Clock, Close, ChevronRight };

    static constexpr const char* glyph(Icon id) {
        switch (id) {
        case Icon::Play: return "\xEE\x84\xBC";                         // U+E13C
        case Icon::Settings: return "\xEE\x8A\x9A";                         // U+E29A sliders-horizontal
        case Icon::Users: return "\xEE\x86\xA4";                         // U+E1A4
        case Icon::FileText: return "\xEE\x83\x8C";                         // U+E0CC
        case Icon::Image: return "\xEE\x83\xB6";                         // U+E0F6
        case Icon::Search: return "\xEE\x85\x91";                         // U+E151
        case Icon::Plus: return "\xEE\x84\xBD";                         // U+E13D
        case Icon::MessageCircle: return "\xEE\x84\x96";                         // U+E116
        case Icon::User: return "\xEE\x86\x9F";                         // U+E19F
        case Icon::ArrowLeftRight: return "\xEE\x89\x8A";                         // U+E24A
        case Icon::Clock: return "\xEE\x82\x87";                         // U+E087
        case Icon::Close: return "\xEE\x86\xB2";                         // U+E1B2 (x)
        case Icon::ChevronRight: return "\xEE\x81\xAF";                         // U+E06F
        }
        return "";
    }

    // `size` is the icon's box in pixels; the glyph is rasterised at the nearest whole pixel size and placed on whole pixels, so its edges are the font's own.
    // The stroke weight is the font's (2/24 of the size).
    static void draw(ImDrawList* d, Icon id, ImVec2 center, float size, ImU32 color) {
        const float s = (std::max)(1.f, std::floorf(size + 0.5f));
        d->AddText(Fonts::icons, s, ImVec2(std::floorf(center.x - s * 0.5f + 0.5f), std::floorf(center.y - s * 0.5f + 0.5f)), color, glyph(id));
    }
};

} // namespace Render
