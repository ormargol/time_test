#include <stdio.h>
#include <math.h>

int options[24][4] = {
	{0, 1, 2, 3},
	{0, 1, 3, 2},
	{0, 2, 1, 3},
	{0, 2, 3, 1},
	{0, 3, 1, 2},
	{0, 3, 2, 1},
	{1, 0, 2, 3},
	{1, 0, 3, 2},
	{1, 2, 0, 3},
	{1, 2, 3, 0},
	{1, 3, 0, 2},
	{1, 3, 2, 0},
	{2, 0, 1, 3},
	{2, 0, 3, 1},
	{2, 1, 0, 3},
	{2, 1, 3, 0},
	{2, 3, 0, 1},
	{2, 3, 1, 0},
	{3, 0, 1, 2},
	{3, 0, 2, 1},
	{3, 1, 0, 2},
	{3, 1, 2, 0},
	{3, 2, 0, 1},
	{3, 2, 1, 0}
};

int sort_digits(int time) {
	int d[4];
	int i, j, temp;
	for (i = 0; i < 4; i++) {
		d[i] = time % 10;
		time /= 10;
	}
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 4; j++) {
			if (d[i] > d[j]) {
				temp = d[j];
				d[j] = d[i];
				d[i] = temp;
			}
		}
	}
	return 1000 * d[3] + 100 * d[2] + 10 * d[1] + d[0];
}

int time_sum(int time1, int time2) {
	int h = time1 / 100 + time2 / 100;
	int m = time1 % 100 + time2 % 100;
	if (m > 60) {
		m -= 60;
		h++;
	}
	return h * 100 + m;
}

int time_sub(int time1, int time2) {
	int h = time1 / 100 - time2 / 100;
	int m = time1 % 100 - time2 % 100;
	if (m < 0) {
		m += 60;
		h++;
	}
	return h * 100 + m;
}

int time_same_digits(int time1, int time2) {
	time1 = sort_digits(time1);
	time2 = sort_digits(time2);
	return time1 == time2;
}

int time_valid(int time) {
	int h = time / 100;
	int m = time % 100;
	return h >=0 && h < 24 && m >= 0 && m < 60;
}

int time_make_options(int time, int opts[]) {
	int digits[4];
	int time_temp = time;
	int i, j = 0, res;
	for (i = 0; i < 4; i++) {
		digits[i] = time_temp % 10;
		time_temp /= 10;
	}
	for (i = 0; i < 24; i++) {
		res = digits[0] * pow(10, options[i][0]);
		res += digits[1] * pow(10, options[i][1]);
		res += digits[2] * pow(10, options[i][2]);
		res += digits[3] * pow(10, options[i][3]);
		if (time_valid(res)) {
			opts[j++] = res;
		}
	}
	return j;
}

int main(int argc, char** argv) {
	int h,m, time, i, size, sum, sub1, sub2;
	int opts[23];
	for (h = 0; h < 24; h++) {
		for (m = 0; m < 60; m++) {
			time = 100 * h + m;
			size = time_make_options(time, opts);
			for (i = 0; i < size; i++) {
				sum = time_sum(time, opts[i]);
				sub1 = time_sub(time, opts[i]);
				sub2 = time_sub(opts[i], time);
				if (time_valid(sum) && time_same_digits(time, sum)) {
					printf("%d + %d = %d\n", time, opts[i], sum);
				}
				if (time_valid(sub1) && time_same_digits(time, sub1)) {
					printf("%d - %d = %d\n", time, opts[i], sub1);
				}
				if (time_valid(sub2) && time_same_digits(time, sub2)) {
					printf("%d - %d = %d\n", opts[i], time, sub2);
				}
			}
		}
	}
	return 0;
}
