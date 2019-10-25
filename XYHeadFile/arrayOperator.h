#pragma once
template <class Type>
void ArrayInitial(Type value[], Type a, unsigned n) {
	for (unsigned i = 0;i < n;++i) {
		value[i] = a;
	}
}

void BinaryPlusOne(unsigned value[],unsigned n) {
	value[0] += 1;
	for (unsigned i = 0;i < n-1;++i) {
		if (value[i] == 2) {
			value[i] = 0;
			value[i + 1] += 1;
		}
	}
	if (value[n - 1] == 2)
		error("function: BinaryPlusOne(unsigned value[],unsigned n) exceed definition, you need to used larger n\n");
}
