/////////////////////////////////////////////////////////////////////////////
// Name:    xyzrenderer.cpp
// Purpose: xyz renderer implementation
// Author:    Moskvichev Andrey V.
// Created:    2009/04/04
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////


#include "wx/xyz/xyzrenderer.h"

IMPLEMENT_CLASS(XYZRenderer, Renderer)

XYZRenderer::XYZRenderer(int minRad, int maxRad)
{
    m_minRad = minRad;
    m_maxRad = maxRad;

    m_defaultPenWidth = 1;
    m_defaultPenStyle = wxPENSTYLE_SOLID;
    m_defaultBrushStyle = wxBRUSHSTYLE_SOLID;
}

XYZRenderer::~XYZRenderer()
{
}

void XYZRenderer::Draw(wxDC &dc, const wxRect& rc, Axis* horizAxis, Axis* vertAxis, NaryDataSet* dataset)
{
    double minZ = dataset->GetMinValue1(2);
    double maxZ = dataset->GetMaxValue1(2);

    double k = (m_maxRad - m_minRad) / (maxZ - minZ);


    FOREACH_SERIE(serie, dataset) {
        dc.SetPen(*GetSeriePen(serie));
        dc.SetBrush(*GetSerieBrush(serie));

        FOREACH_DATAITEM(n, serie, dataset) {
            double xVal;
            double yVal;
            double zVal;

            xVal = dataset->InterpretDataAsValue(serie, n, 0);
            yVal = dataset->InterpretDataAsValue(serie, n, 1);
            zVal = dataset->InterpretDataAsValue(serie, n, 2);

            wxCoord x = horizAxis->ToGraphics(dc, rc.x, rc.width, xVal);
            wxCoord y = vertAxis->ToGraphics(dc, rc.y, rc.height, yVal);

            wxCoord r = (wxCoord) ((zVal - minZ) * k + m_minRad);

            dc.DrawCircle(x, y, r);
        }
    }
}

void XYZRenderer::SetSeriePen(size_t serie, wxPen *pen)
{
    m_seriePens[serie] = *pen;
}

void XYZRenderer::SetSerieColor(size_t serie, wxColour *color)
{
    SetSeriePen(serie, wxThePenList->FindOrCreatePen(*color, m_defaultPenWidth, m_defaultPenStyle));
    SetSerieBrush(serie, wxTheBrushList->FindOrCreateBrush(*color, m_defaultBrushStyle));
}

wxColour XYZRenderer::GetSerieColor(size_t serie)
{
    if (m_serieBrushs.find(serie) == m_serieBrushs.end()) {
        return GetDefaultColour(serie);
    }
    return m_serieBrushs[serie].GetColour();
}

wxPen *XYZRenderer::GetSeriePen(size_t serie)
{
    if (m_seriePens.find(serie) == m_seriePens.end()) {
        return wxThePenList->FindOrCreatePen(GetDefaultColour(serie), m_defaultPenWidth, m_defaultPenStyle);
    }
    return &m_seriePens[serie];
}

void XYZRenderer::SetSerieBrush(size_t serie, wxBrush *brush)
{
    m_serieBrushs[serie] = *brush;
}

wxBrush *XYZRenderer::GetSerieBrush(size_t serie)
{
    if (m_serieBrushs.find(serie) == m_serieBrushs.end()) {
        return wxTheBrushList->FindOrCreateBrush(GetDefaultColour(serie), m_defaultBrushStyle);
    }
    return &m_serieBrushs[serie];
}
