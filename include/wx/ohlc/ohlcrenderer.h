/////////////////////////////////////////////////////////////////////////////
// Name:    ohlcrenderer.h
// Purpose: OHLC renderers base class declaration.
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef OHLCRENDERER_H_
#define OHLCRENDERER_H_

#include <wx/chartrenderer.h>
#include <wx/xy/xyrenderer.h>
#include <wx/xy/xydataset.h>

/**
 * Class that controls bars/candlesticks colour.
 * It's used to implement bar colo
 */
class WXDLLIMPEXP_FREECHART OHLCColourer
{
public:
    // IY: Virtual destructor needed otherwise behaviour is undefined.
    virtual ~OHLCColourer() {}
    virtual wxColor GetColour (int step) = 0;
};

/**
 * Base class for rendering OHLC data.
 */
class WXDLLIMPEXP_FREECHART OHLCRenderer : public XYRenderer
{
public:
    OHLCRenderer();
    virtual ~OHLCRenderer();

    /**
     * Draws item.
     * @param dc device context
     * @param x coordinate
     * @param open open value in graphical coordinates
     * @param high high value in graphical coordinates
     * @param low low value in graphical coordinates
     * @param close close value in graphical coordinates
     */
    virtual void DrawItem (wxDC &dc, wxCoord x, wxCoord open, wxCoord high, wxCoord low, wxCoord close) = 0;

    virtual void Draw (wxDC& dc, const wxRect& rc, Axis* xAxis, Axis* yAxis, BiDataSet* dataset) {}
    virtual void Draw (wxDC& dc, wxRect rc, Axis* horizAxis, Axis* vertAxis, XYDataset* dataset) {}
    virtual double GetMax(const Dataset* dataset, size_t dimension) const;
    virtual double GetMin(const Dataset* dataset, size_t dimension) const;

    void SetColourer (OHLCColourer *colourer);
    OHLCColourer *GetColourer();

protected:
    OHLCColourer *m_colourer;
};

#endif /*OHLCRENDERER_H_*/
