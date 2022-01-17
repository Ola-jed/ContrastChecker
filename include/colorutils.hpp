#ifndef COLORPALETTE_HPP
#define COLORPALETTE_HPP

#include <QColor>
#include <cmath>
namespace colorUtils
{
    inline double computeLuminance(const QColor& color)
    {
        const auto r = color.red() / 255.;
        const auto g = color.green() / 255.;
        const auto b = color.blue() / 255.;
        const auto sr = r <= 0.03928 ? r / 12.92 : std::pow((r + 0.055) / 1.055, 2.4);
        const auto sg = g <= 0.03928 ? g / 12.92 : std::pow((g + 0.055) / 1.055, 2.4);
        const auto sb = b <= 0.03928 ? b / 12.92 : std::pow((b + 0.055) / 1.055, 2.4);
        return 0.2126 * sr + 0.7152 * sg + 0.0722 * sb;
    }

    inline double computeContrastRatio(const QColor& color1,const QColor& color2)
    {
        const auto lum1 = computeLuminance(color1);
        const auto lum2 = computeLuminance(color2);
        const auto brightest = std::max(lum1, lum2);
        const auto darkest = std::min(lum1, lum2);
        return (brightest + 0.05) / (darkest + 0.05);
    }
}

#endif // COLORPALETTE_HPP
