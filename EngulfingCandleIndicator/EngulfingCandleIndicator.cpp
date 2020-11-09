//---------------------------------------------------------------------------
// Engulfing Candle Indicator 
// Ray Hancock 2020
//---------------------------------------------------------------------------

#include <windows.h>
#include "IndicatorInterfaceUnit.h"
#include "TechnicalFunctions.h"

//// External variables
bool EnableIndicator;

//// Buffers
TIndexBuffer
BullEngulfing1, BullEngulfing2, BullEngulfing3, BullEngulfing4,
BearEngulfing1, BearEngulfing2, BearEngulfing3, BearEngulfing4;

//---------------------------------------------------------------------------
// Initialize indicator
//---------------------------------------------------------------------------
EXPORT void __stdcall Init()
{
	// define properties
	IndicatorShortName("Engulfing Candle");
	SetOutputWindow(ow_ChartWindow);
	SetEmptyValue(-1);

	BullEngulfing1 = CreateIndexBuffer();
	BullEngulfing2 = CreateIndexBuffer();
	BullEngulfing3 = CreateIndexBuffer();
	BullEngulfing4 = CreateIndexBuffer();

	BearEngulfing1 = CreateIndexBuffer();
	BearEngulfing2 = CreateIndexBuffer();
	BearEngulfing3 = CreateIndexBuffer();
	BearEngulfing4 = CreateIndexBuffer();

	IndicatorBuffers(8);

	RegOption("Enable indicator", ot_Boolean, &EnableIndicator);
	EnableIndicator = true;

	AddSeparator("Up Bar");

	SetIndexBuffer(0, BullEngulfing1);
	SetIndexStyle(0, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(0, "up wick");

	SetIndexBuffer(1, BullEngulfing2);
	SetIndexStyle(1, ds_None, psSolid, 1, clGreen);
	SetIndexLabel(1, "up filler");

	SetIndexBuffer(2, BullEngulfing3);
	SetIndexStyle(2, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(2, "down wick");

	SetIndexBuffer(3, BullEngulfing4);
	SetIndexStyle(3, ds_ColoredCandles, psSolid, 1, clGreen);
	SetIndexLabel(3, "down filler");

	AddSeparator("Down Bar");

	SetIndexBuffer(4, BearEngulfing1);
	SetIndexStyle(4, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(4, "up wick");

	SetIndexBuffer(5, BearEngulfing2);
	SetIndexStyle(5, ds_None, psSolid, 1, clRed);
	SetIndexLabel(5, "up filler");

	SetIndexBuffer(6, BearEngulfing3);
	SetIndexStyle(6, ds_None, psSolid, 1, clBlack);
	SetIndexLabel(6, "down wick");

	SetIndexBuffer(7, BearEngulfing4);
	SetIndexStyle(7, ds_ColoredCandles, psSolid, 1, clRed);
	SetIndexLabel(7, "down filler");
}

EXPORT void __stdcall OnParamsChange()
{
}

//---------------------------------------------------------------------------
// Calculate requested bar
//---------------------------------------------------------------------------
EXPORT void __stdcall Calculate(int index)
{
	// Add extended range candles (candle * 0.8)

	double open, close, high, low, prevClose, prevOpen;
	int emptyValue;

	open = Open(index);
	high = High(index);
	low = Low(index);
	close = Close(index);

	prevClose = Close(index + 1);
	prevOpen = Open(index + 1);

	emptyValue = -1;

	// Use_BullEngulfing
	if (((close > open) && (prevClose < prevOpen) && (close >= prevOpen) && (open <= prevClose)) && EnableIndicator)
	{
		BullEngulfing1[index] = open;
		BullEngulfing2[index] = high;
		BullEngulfing3[index] = low;
		BullEngulfing4[index] = close;
	}
	else
	{
		BullEngulfing1[index] = emptyValue;
		BullEngulfing2[index] = emptyValue;
		BullEngulfing3[index] = emptyValue;
		BullEngulfing4[index] = emptyValue;
	}

	//Use_BearEngulfing
	if (((close < open) && (prevClose > prevOpen) && (open >= prevClose) && (close <= prevOpen)) && EnableIndicator)
	{
		BearEngulfing1[index] = open;
		BearEngulfing2[index] = high;
		BearEngulfing3[index] = low;
		BearEngulfing4[index] = close;
	}
	else
	{
		BearEngulfing1[index] = emptyValue;
		BearEngulfing2[index] = emptyValue;
		BearEngulfing3[index] = emptyValue;
		BearEngulfing4[index] = emptyValue;
	}
}
