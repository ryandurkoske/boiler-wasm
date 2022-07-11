#pragma once

#include <stdint.h>

struct example_struct {
	int32_t a;
	int32_t b;
};

int32_t compute_example(struct example_struct);