#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <TinyXML2/tinyxml2.h>

#define MAX_DATA_LEN 255
#define MAX_NODE_LEN 255
#define MAX_NODE_NAME 64

using namespace tinyxml2;


typedef struct node
{
	char name[MAX_NODE_NAME];
	char data[MAX_DATA_LEN];
	int num;
	struct node *right, *child;
} Node;

char *file_to_data(FILE *fp)
{
	long length=0;
	char c=0;
	short isInString=0, isInName=0, lastWasNum=0;

	fseek(fp, 0, SEEK_SET);

	while ((c = (char)fgetc(fp)) != EOF)
	{
		if (c == '"') isInString = ~isInString;

		if (!isInString && !lastWasNum && (c == ' '|| c == '\n' || c == '\r' || c == '\t')) continue;

		if (c >= '0' && c <= '9') lastWasNum=1;
		else lastWasNum=0;

		length++;
	}

	fseek(fp, 0, SEEK_SET);
	char* data = (char*)malloc(length+1);

	c=0, length=0, isInString=0, lastWasNum=0;
	while ((c = (char)fgetc(fp)) != EOF)
	{
		if (c == '"') isInString = ~isInString;

		if (!isInString && !lastWasNum && (c == ' '|| c == '\n' || c == '\r' || c == '\t')) continue;

		if (c >= '0' && c <= '9') lastWasNum=1;
		else lastWasNum=0;

		*(data+length) = c;

		length++;
	}

	*(data+length) = 0;

	fseek(fp, 0, SEEK_SET);

	return data;
}

void push_brother(Node *n, Node *brother)
{
	if (!n->right) { n->right = brother; return; }

	Node *temp = NULL;

	while ((temp = n->right) != NULL)
		n=temp;

	n->right = brother;
}

Node* parse_data(char *data, const char *name)
{
	long data_len = strlen(data);
	Node *n = (Node*)malloc(sizeof(struct node));

	// initialize
	strcpy(n->name, name);
	memset(n->data, 0, MAX_DATA_LEN*sizeof(char));
	n->right = n->child = NULL;
	n->num = 0;

	long pos=0, openChildBracket=-1;
	short lev = 0;

	while (pos < data_len) {
		if (*(data+pos) == '(' && lev==0)
			openChildBracket=pos;

		if (*(data+pos) == '(') lev++;
		if (*(data+pos) == ')') lev--;

		if (*(data+pos) == ')' && lev==0)
		{
			char node[MAX_NODE_LEN];
			memset(node, 0, MAX_NODE_LEN*sizeof(char));

			long start = openChildBracket+1;
			long len = pos-openChildBracket-1;

			memcpy(node, data+start, len);
			
			// parse node
			char* node_start = strstr(node, "(");
			if (node_start)
			{
				// cut name
				char node_name[MAX_NODE_NAME];
				memset(node_name, 0, MAX_NODE_NAME*sizeof(char));
				
				memcpy(node_name, data+start, len-strlen(node_start));

				//printf("Parsing node name <%s>: [%s]\n", node_name, node+len-strlen(node_start));
				Node *child = parse_data(node+len-strlen(node_start), node_name);

				if (n->child)
					push_brother(n->child, child);
				else n->child = child;
			}
			// leaf
			else
			{
				// init leaf
				Node *leaf = (Node*)malloc(sizeof(struct node));
				leaf->child = NULL;
				leaf->right = NULL;

				int j=0;
				while(j < len && *(node+j) != '"') j++;
				
				// "String"
				if (j != len)
				{
					char node_data[MAX_DATA_LEN];
					memset(node_data, 0, MAX_DATA_LEN*sizeof(char));
					memcpy(node_data, node+j+1, len-j-2);
					strcpy(leaf->data, node_data);

					char node_name[MAX_NODE_NAME];
					memset(node_name, 0, MAX_NODE_NAME*sizeof(char));
					memcpy(node_name, node, j);
					strcpy(leaf->name, node_name);

					leaf->num=0;

					//printf("Leaf: string: %s=[%s]\n", node_name, node_data);
				}
				// Int
				else
				{
					j=0;
					while (j < len && (*(node+j) < 48 || *(node+j) > 57)) j++;

					char node_name[MAX_NODE_NAME];
					memset(node_name, 0, MAX_NODE_NAME*sizeof(char));
					memcpy(node_name, node, j);
					strcpy(leaf->name, node_name);

					char node_data[MAX_DATA_LEN];
					memset(node_data, 0, MAX_DATA_LEN*sizeof(char));
					memcpy(node_data, node+j, len-j);
					strcpy(leaf->data, node_data);

					leaf->num = atoi(node_data);

					//printf("Leaf: int: %s=[%d]\n", leaf->name, leaf->num);
				}
				
				if (n->child)
					push_brother(n->child, leaf);
				else n->child = leaf;
			}

			openChildBracket=0;
		}

		pos++;
	}

	return n;
}

short parse_init_file(FILE *fp, Node *root)
{
	char *data = file_to_data(fp);
	if (!data) return -1;

	//printf("Data:\n%s\n", data);
	Node *newroot = parse_data(data, "root");
	memcpy(root, newroot, sizeof(struct node));

	free(data);
	return 0;
}

short parser_init(const char *filename, Node *root)
{
	FILE *fp = fopen(filename, "r");
	if (!fp) return -1;

	if (parse_init_file(fp, root) == -1)
	{
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return 0;
}

void print_config(Node *n)
{
	Node *temp = n;
	
	while (temp->right != NULL)
	{
		print_config(temp->right);
		temp = temp->right;
	}

	if (temp->child)
		print_config(temp->child);

	//printf("[%s]\n|%s|\n|%d|\n", n->name, n->data, n->num);
}

void initnpc_to_xml(Node *n, const char* outputPath)
{
	FILE *fp = fopen(outputPath, "w+");
	if (!fp) {
		printf("Cannot create %s.\n", outputPath);
		return;
	}

	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><world></world>");

	fclose(fp);

	XMLDocument doc;

	if (doc.LoadFile(outputPath) != XML_SUCCESS)
	{
		printf("Cannot open %s. (%s)\n", outputPath, doc.ErrorName());
		return;
	}
	
	XMLElement *pRoot = doc.RootElement();
	if (!pRoot)
	{
		printf("Can't find root.\n");
		return;
	}

	pRoot->DeleteChildren();

	Node *temp = n->child;

	while (temp != NULL)
	{
		if (temp->child) {
			Node *tmpprop = temp->child;

			XMLElement *pEle = doc.NewElement("npc")->ToElement();

			while (tmpprop != NULL)
			{
				if (!strcmp(tmpprop->name, "index")) {
					pEle->SetAttribute("index", tmpprop->num);
				}
				else if (!strcmp(tmpprop->name, "shape"))
					pEle->SetAttribute("shape", tmpprop->num);
				else if (!strcmp(tmpprop->name, "html"))
					pEle->SetAttribute("html", tmpprop->num);
				else if (!strcmp(tmpprop->name, "xy")) {
					char *token = std::strtok(tmpprop->data, " ");
					if (token) {
						pEle->SetAttribute("x", atoi(token));
						token = std::strtok(NULL, " ");
						if (token) {
							pEle->SetAttribute("y", atoi(token));
							token = std::strtok(NULL, " ");
							if (token) pEle->SetAttribute("z", atoi(token));
						}
					}
				}
				else if (!strcmp(tmpprop->name, "dir")) {
					char *token = std::strtok(tmpprop->data, " ");
					if (token) {
						pEle->SetAttribute("dirx", atoi(token));
						token = std::strtok(NULL, " ");
						if (token) pEle->SetAttribute("diry", atoi(token));
					}
				}

				tmpprop = tmpprop->right;
			}

			pRoot->InsertEndChild(pEle);
		}

		temp = temp->right;
	}

	doc.SaveFile(outputPath);
	printf("Converting succeeded.\n");
}

int main(int argc, char** argv)
{
	if (argc < 4) {
		printf("Bad argumentlist. ([type] [input] [output])\nExample: ./%s InitNPC InitNPC.txt InitNPC.xml\n", argv[0]);
		return 1;
	}

	Node root;

	if (parser_init(argv[2], &root) == -1){
		printf("Cannot open %s.\n", argv[2]);
		return 1;
	}

	if (!strcmp(argv[1], "InitNPC"))
		initnpc_to_xml(&root, argv[3]);
	else
		printf("%s is not available.\n", argv[1]);

	return 0;
}