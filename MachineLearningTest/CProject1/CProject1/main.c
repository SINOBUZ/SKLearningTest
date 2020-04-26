#include <stdio.h>
#include <json.h>
#include <stdlib.h>
#include <string.h>

char *readFile(char *filename, int *readSize)    // 파일을 읽어서 내용을 반환하는 함수
{
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL)
		return NULL;

	int size;
	char *buffer;

	// 파일 크기 구하기
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// 파일 크기 + NULL 공간만큼 메모리를 할당하고 0으로 초기화
	buffer = malloc(size + 1);
	memset(buffer, 0, size + 1);

	// 파일 내용 읽기
	if (fread(buffer, size, 1, fp) < 1)
	{
		*readSize = 0;
		free(buffer);
		fclose(fp);
		return NULL;
	}

	// 파일 크기를 넘겨줌
	*readSize = size;

	fclose(fp);    // 파일 포인터 닫기

	return buffer;
}

int main()
{
	int size;    // 문서 크기
	enum json_type type;
	// 파일에서 JSON 문서를 읽음, 문서 크기를 구함
	char *doc = readFile("example.json", &size);
	if (doc == NULL)
		return -1;
	json_object *jobj = json_tokener_parse(doc);
	json_object_object_foreach(jobj, key, val)
	{
		// get current json object type
		type = json_object_get_type(val);
		printf("type = ");

		switch (type)
		{
		case json_type_null:
			printf("json_type_null\n");
			break;
		case json_type_boolean:
			printf("json_type_boolean\n");
			printf("key = %-15s : value = %s\n", key, json_object_get_boolean(val) ? "true" : "false");
			break;
		case json_type_double:
			printf("json_type_double\n");
			printf("key = %-15s : value = %lf\n", key, json_object_get_double(val));
			break;
		case json_type_int:
			printf("json_type_int\n");
			printf("key = %-15s : value = %d\n", key, json_object_get_int(val));
			break;
		case json_type_object:
			printf("json_type_object\n");
			printf("key = %-15s : value = \n", key);
			break;
		case json_type_array:
			printf("json_type_array\n");
			printf("key = %-15s : value = \n", key);
			break;
		case json_type_string:
			printf("json_type_string\n");
			printf("key = %-15s : value = %s\n", key, json_object_get_string(val));
			break;
		}
	}

	printf("\n");

	return 0;
}