/**
* Stores a lookup table, in the form of two parallel arrays.  Used to sample from arbitrary distributions.
*/

#pragma once

#include "LookupTable.generated.h"

UCLASS()
class ULookupTable : public UObject
{
    GENERATED_BODY()

public:

    ULookupTable();

    /**
    * Initialize the lookup table.  Stores the arrays provided, and stores their min and max values so we can use those later without searching.
    * @param Xin - X values; MUST ALREADY BE SORTED in increasing order.
    * @param Yin - Y values; NOT assumed to be sorted.
    */
    UFUNCTION()
    void Init(TArray<float> Xin, TArray<float> Yin);

    /**
     * Initialize the lookup table from a CSV file, which this function will read in.
     * The file should have exactly 2 columns; the
     * first will be X and the second will be Y.
     * @param CSVFilePath - The name WITH FULL PATH of the CSV file to load.
     * @return True if the it was successful, false if there were problems.
     */
    UFUNCTION()
    bool InitFromCSVFile(const FString &CSVFilePath);

    /**
     * Get a table y-value.  Finds the largest X value that's <= the given X (i.e. nearest without going over).  If the input value is out of range, the first or last output value is used.
     * 
     * ASSUMES the X values are evenly spaced and increasing monotonically.  (This allows very fast lookups.)
     * 
     * @param X - The x-value to look up.
     * @return The corresponding y-value.
     */
    UFUNCTION()
    float Lookup(float X);

    /**
    * Get a table y-value.  Interpolates linearly between the nearest X values.  If the input value is out of range, the first or last output value is used.
    * @param X - The x value to look up.
    * @return The corresponding y-value.
    */
    UFUNCTION()
        float Lookup_Interpolate(float X);

    UFUNCTION()
        float GetXmin();

    UFUNCTION()
        float GetXmax();

    UFUNCTION()
        float GetYmin();

    UFUNCTION()
        float GetYmax();

private:

    /** The x values for each entry. */
    UPROPERTY()
        TArray<float> Xarr;

    /** The y values for each entry. */
    UPROPERTY()
        TArray<float> Yarr;

    UPROPERTY()
        float Xmin;

    UPROPERTY()
        float Xmax;

    UPROPERTY()
        float Ymin;

    UPROPERTY()
        float Ymax;

};

