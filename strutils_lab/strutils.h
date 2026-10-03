#ifndef STRUTILS_H
#define STRUTILS_H

/* Đảo ngược chuỗi tại chỗ. s phải là mảng ghi được. NULL thì bỏ qua. */
void str_reverse(char *s);

/* Xoá khoảng trắng ở đầu và cuối chuỗi (tại chỗ). NULL thì bỏ qua. */
void str_trim(char *s);

/*
 * Chuyển chuỗi sang int một cách an toàn.
 * Trả về 0 nếu thành công (kết quả ghi vào *out),
 * trả về -1 nếu đầu vào không hợp lệ (NULL, rỗng, có ký tự lạ, tràn số).
 */
int str_to_int(const char *s, int *out);

#endif /* STRUTILS_H */
