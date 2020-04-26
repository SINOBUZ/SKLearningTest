#include <stdio.h>
#include <json.h>
#include <stdlib.h>
#include <string.h>

char *readFile(char *filename, int *readSize)    // ������ �о ������ ��ȯ�ϴ� �Լ�
{
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL)
		return NULL;

	int size;
	char *buffer;

	// ���� ũ�� ���ϱ�
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// ���� ũ�� + NULL ������ŭ �޸𸮸� �Ҵ��ϰ� 0���� �ʱ�ȭ
	buffer = malloc(size + 1);
	memset(buffer, 0, size + 1);

	// ���� ���� �б�
	if (fread(buffer, size, 1, fp) < 1)
	{
		*readSize = 0;
		free(buffer);
		fclose(fp);
		return NULL;
	}

	// ���� ũ�⸦ �Ѱ���
	*readSize = size;

	fclose(fp);    // ���� ������ �ݱ�

	return buffer;
}

int main()
{
	int size;    // ���� ũ��
	enum json_type type;
	// ���Ͽ��� JSON ������ ����, ���� ũ�⸦ ����
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