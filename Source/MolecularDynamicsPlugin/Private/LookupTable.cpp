// Fill out your copyright notice in the Description page of Project Settings.

#include "LookupTable.h"
#include "Misc/CString.h"
#include "Misc/FileHelper.h"

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
    UE_LOG(LogTemp, Warning, TEXT("ULookupTable::Init() Called Xin.Num():%d - Yin.Num():%d - Xarr.Num():%d - Yarr.Num():%d - Xmin:%f - XMax:%f - Ymin:%e - Ymax:%e"), Xin.Num(), Yin.Num(), Xarr.Num(), Yarr.Num(), Xmin, Xmax, Ymin, Ymax);
}

bool ULookupTable::InitFromCSVFile(const FString& CSVFilePath) {
	UE_LOG(LogTemp, Warning, TEXT("ULookupTable::InitFromCSVFile() Called."))
    TArray<FString> lines;
    TArray<FString> items;
    TArray<float> Xin;
    TArray<float> Yin;
    int32 nItems;
    bool success;
    success = FFileHelper::LoadFileToStringArray(lines, *CSVFilePath);
    if (success) {
        UE_LOG(LogTemp, Warning, TEXT("ULookupTable::InitFromCSVFile() Successfully loaded CSV file %s - NumLines:%d"), *CSVFilePath, lines.Num());
    	for (int32 iline = 0; iline < lines.Num(); ++iline) {
            //UE_LOG(LogTemp, Warning, TEXT("ULookupTable::InitFromCSVFile() iline:%d - line:%s"), iline, *lines[iline]);
            nItems = lines[iline].FString::ParseIntoArray(items, TEXT(","), false);
            if (nItems != 2) {
                UE_LOG(LogTemp, Warning, TEXT("ULookupTable::InitFromCSVFile ERROR! Found %i items per row in CSV file (expecting 2)."), nItems);
                return false;
            }
            //UE_LOG(LogTemp, Warning, TEXT("ULookupTable::InitFromCSVFile() iline:%d - XIn:%s - YIn:%s"), iline, *items[0], *items[1]);
            Xin.Add(FCString::Atof(*items[0]));
            Yin.Add(FCString::Atof(*items[1]));
        }
        UE_LOG(LogTemp, Warning, TEXT("ULookupTable::InitFromCSVFile() Successfully loaded %d lines from CSV file."), lines.Num());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ULookupTable::InitFromCSVFile() Failed to load CSV file %s"), *CSVFilePath);
    	return false;
    }

    Init(Xin, Yin);

    return true;
}

    float
    ULookupTable::GetXmin()
{
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

float ULookupTable::Lookup(float X)
{
    //UE_LOG(LogTemp, Warning, TEXT("ULookupTable::Lookup(%f) called."), X);
	if(Yarr.Num() > 0)
	{
		int index;
	    //float pos, Y;
	    float pos;
	    
		
	    if (X <= Xmin)
	    {

	    	UE_LOG(LogTemp, Error, TEXT("ULookupTable::Lookup(%f) <= Xmin return:%e ."), X, Yarr[0]);
	        return Yarr[0];
	    }
	    else if (X >= Xmax)
	    {
            UE_LOG(LogTemp, Error, TEXT("ULookupTable::Lookup(%f) >= Xmin return:%e ."), X, Yarr[0]);
	        return Yarr.Last(0);
	    }

	    // Calculate the appropriate index.
	    pos = float(Xarr.Num()) * (X - Xmin) / (Xmax - Xmin);
	    index = FMath::Floor(pos);

        //float ReturnValue = Yarr[index];
        //UE_LOG(LogTemp, Warning, TEXT("ULookupTable::Lookup(%f) Index:%d - Returns:%e."), X, index, ReturnValue);
        //return ReturnValue;
		return Yarr[index];
	    //return Yarr[0];
	}
    UE_LOG(LogTemp, Error, TEXT("ULookupTable::Lookup(%f) Failed, YArr empty! Yarr.Num():%d"), X, Yarr.Num());
    return 0.0f;
}

float ULookupTable::Lookup_Interpolate(float X)
{
    int32 i1, i2, imid;
    float Y, dY;

    if (X <= Xmin) 
    {
        return Yarr[0];
    }
	else if (X >= Xmax) 
    {
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
