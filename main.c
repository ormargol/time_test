#include <stdio.h>

int options[24][4] = {
	{1, 10, 100, 1000},
	{1, 10, 1000, 100},
	{1, 100, 10, 1000},
	{1, 100, 1000, 10},
	{1, 1000, 10, 100},
	{1, 1000, 100, 10},
	{10, 1, 100, 1000},
	{10, 1, 1000, 100},
	{10, 100, 1, 1000},
	{10, 100, 1000, 1},
	{10, 1000, 1, 100},
	{10, 1000, 100, 1},
	{100, 1, 10, 1000},
	{100, 1, 1000, 10},
	{100, 10, 1, 1000},
	{100, 10, 1000, 1},
	{100, 1000, 1, 10},
	{100, 1000, 10, 1},
	{1000, 1, 10, 100},
	{1000, 1, 100, 10},
	{1000, 10, 1, 100},
	{1000, 10, 100, 1},
	{1000, 100, 1, 10},
	{1000, 100, 10, 1}
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
		res = digits[0] * options[i][0];
		res += digits[1] * options[i][1];
		res += digits[2] * options[i][2];
		res += digits[3] * options[i][3];
		if (time_valid(res)) {
			opts[j++] = res;
		}
	}
	return j;
}

void time_print(int time) {
	int h = time / 100;
	int m = time % 100;
	if (h < 10) {
		printf("0");
	}
	printf("%d:", h);
	if (m < 10) {
		printf("0");
	}
	printf("%d", m);
}
int main(int argc, char** argv) {
	int h,m, time, i, j, size, sum;
	int opts[23];
	int res1[100], res2[100];
	int res_count = 0;
	int flag_found;
	for (h = 0; h < 24; h++) {
		for (m = 0; m < 60; m++) {
			time = 100 * h + m;
			size = time_make_options(time, opts);
			for (i = 0; i < size; i++) {
				sum = time_sum(time, opts[i]);
				if (time_valid(sum) && time_same_digits(time, sum)) {
					flag_found = 0;
					for (j = 0; j < res_count && !flag_found; j++) {
						if (time == res1[j] && opts[i] == res2[j]) {
							flag_found = 1;
						}
					}
					if (!flag_found) {
						res1[res_count] = time;
						res2[res_count] = opts[i];
						res_count++;
						time_print(time);
						printf(" + ");
						time_print(opts[i]);
						printf(" = ");
						time_print(sum);
						printf("\n");
					}
				}
			}
		}
	}
	return 0;
}
