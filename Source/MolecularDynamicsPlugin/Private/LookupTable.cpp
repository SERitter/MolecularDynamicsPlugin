// Fill out your copyright notice in the Description page of Project Settings.

#include "LookupTable.h"

ULookupTable::ULookupTable() {
    // Empty default constructor.
}

void ULookupTable::Init(TArray<float> Xin, TArray<float> Yin) {
    Xarr = Xin;
    Yarr = Yin;

    Xmin = FMath::Min(Xarr);
    Xmax = FMath::Max(Xarr);
    Ymin = FMath::Min(Yarr);
    Ymax = FMath::Max(Yarr);
}

float ULookupTable::GetXmin() {
    return Xmin;
}

float ULookupTable::GetXmax() {
    return Xmax;
}

float ULookupTable::GetYmin() {
    return Ymin;
}

float ULookupTable::GetYmax() {
    return Ymax;
}

float ULookupTable::Lookup(float X) {
    int32 i1, i2, imid;
    float Y, dY;

    if (X <= Xmin) {
        return Yarr[0];
    } else if (X >= Xmax) {
        return Yarr.Last(0);
    } 

    // Since (we're assuming) Xarr is sorted, we can use a binary search to find the two entries
    // that bracket the desired X.
    i1 = 0;
    i2 = Xarr.Num() - 1;
    while (i2 - i1 > 1) {
        imid = (i1 + i2) / 2;
        if (X >= Xarr[imid]) {
            i1 = imid;
        } else {
            i2 = imid;
        }
    }

    // We've found the interval; now to interpolate.
    dY = (Yarr[i2] - Yarr[i1]) * (X - Xarr[i1]) / (Xarr[i2] - Xarr[i1]);
    Y = Yarr[i1] + dY;

    return Y;
}
