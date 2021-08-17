# Generate a normal distribution inverse-CDF lookup table,
# and output commands to push the CDF into an array/vector in 
# another programming language.

# Use 1002 points because 0 and 1 give infinity,
# so this leaves us with 1000 useful points.
x = seq(0, 1, length.out=1002)
y = qnorm(x)

sink(file="NormCDF_problist_code.txt")
for (i in 1:length(x)) {
	if (is.finite(y[i])) {
		cat(paste0("Prob.push(", x[i], ");\n"))
	}
}
sink(file=NULL)

sink(file="NormCDF_code.txt")
for (i in 1:length(x)) {
	if (is.finite(y[i])) {
		cat(paste0("CDF.push(", y[i], ");\n"))
	}
}
sink(file=NULL)
