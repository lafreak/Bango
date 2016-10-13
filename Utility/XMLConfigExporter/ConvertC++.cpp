#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <TinyXML2/tinyxml2.h>

using namespace tinyxml2;

class Node
{
public:
	std::string data;

	std::vector<Node*> children;

	~Node()
	{
		for(auto& n: children)
			delete n;
	}
};

class Document
{
public:
	char *raw;
	long length;
	Node* root;

	Document()
	{
		root = new Node;
		raw = NULL;
	}

	~Document()
	{
		delete root;
		if (raw)
			delete raw;
	}

	bool LoadFile(const char *fileName)
	{
		char c;

		std::fstream f(fileName);
		if (!f) return false;
		f.unsetf(std::ios_base::skipws);

		bool isCommentLine=false;
		bool lastWasWhite=false;

		long len=0;
		while (f >> c)
		{
			if (c==';') isCommentLine=true;
			else if (isCommentLine && c == '\n') isCommentLine=false;

			if (isCommentLine) continue;

			if ((c==' ' || c=='\t') && lastWasWhite) continue;
			if (c==' ' || c=='\t') lastWasWhite=true;
			else lastWasWhite=false;

			if (c== '\n' || c=='\r') continue;

			len++;
		}

		raw = new char[len+1];

		//printf("Len: %li\n", len);

		f.close();

		std::fstream g(fileName);
		if (!g) return false;
		g.unsetf(std::ios_base::skipws);

		isCommentLine=false;
		lastWasWhite=false;
		len=0;
		while (g >> c)
		{
			if (c==';') isCommentLine=true;
			else if (isCommentLine && c == '\n') isCommentLine=false;

			if (isCommentLine) continue;

			if ((c==' ' || c=='\t') && lastWasWhite) continue;
			if (c==' ' || c=='\t') lastWasWhite=true;
			else lastWasWhite=false;

			if (c== '\n' || c=='\r') continue;

			raw[len] = c;
			len++;
		}

		raw[len] = 0;

		//printf("Len: %li\n", len);
		length = len;

		return true;
	}

	void Parse(Node *n)
	{
		int lev=0;
		long cur=0;
		long node_start=0;

		long ndlen = n->data.length();
		while (cur < ndlen)
		{
			if (n->data[cur] == '(') {
				if (lev == 0)
					node_start = cur+1;
				lev++;
			}
			else if (n->data[cur] == ')') {
				lev--;

				if (lev == 0) {
					int m = (int)(cur-node_start);
					if (m > 0 ) {
						Node* node = new Node;
						node->data = std::string(n->data.c_str()+node_start, m);
						n->children.push_back(node);
					}
				}
			}
			cur++;
		}

		for (auto& a: n->children)
			Parse(a);
	}

	void Parse()
	{
		int lev=0;
		long cur=0;
		long node_start=0;

		while (cur < length)
		{
			if (raw[cur] == '(') {
				if (lev == 0)
					node_start = cur+1;
				lev++;
			}
			else if (raw[cur] == ')') {
				lev--;

				if (lev == 0) {
					int m = (int)(cur-node_start);
					if (m > 0) {
						Node* node = new Node;
						node->data = std::string(raw+node_start, m);
						root->children.push_back(node);
					}
				}
			}
			cur++;
		}

		for (auto& n: root->children)
			Parse(n);
		
	}

	void InitNPCToXML(const char* outputPath)
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

		for (auto& npc: root->children)
		{
			XMLElement *pEle = doc.NewElement("npc")->ToElement();

			for (auto& prop: npc->children)
			{
				std::istringstream iss(prop->data);
				std::string name;

				iss >> name;

				std::transform(name.begin(), name.end(), name.begin(), ::tolower);

				if (name == "index") {
					int nIndex=0;
					iss >> nIndex;
					pEle->SetAttribute("index", nIndex);
				}

				else if (name == "shape") {
					int nShape=0;
					iss >> nShape;
					pEle->SetAttribute("shape", nShape);
				}

				else if (name == "html") {
					int nHtml=0;
					iss >> nHtml;
					pEle->SetAttribute("html", nHtml);
				}

				else if (name == "xy") {
					int nX=0, nY=0, nZ=0;
					iss >> nX >> nY >> nZ;
					pEle->SetAttribute("x", nX);
					pEle->SetAttribute("y", nY);
					pEle->SetAttribute("z", nZ);
				}

				else if (name == "dir") {
					int nDirX=0, nDirY=0;
					iss >> nDirX >> nDirY;
					pEle->SetAttribute("dirx", nDirX);
					pEle->SetAttribute("diry", nDirY);
				}
			}

			pRoot->InsertEndChild(pEle);
		}

		doc.SaveFile(outputPath);
		printf("Converting succeeded.\n");
	}

	void InitItemToXML(const char* outputPath)
	{
		FILE *fp = fopen(outputPath, "w+");
		if (!fp) {
			printf("Cannot create %s.\n", outputPath);
			return;
		}

		fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><itemlist></itemlist>");
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


		for (auto& item: root->children)
		{
			XMLElement *pEle = doc.NewElement("item")->ToElement();

			for (auto& prop: item->children)
			{
				std::istringstream iss(prop->data);
				std::string name;

				iss >> name;


				std::transform(name.begin(), name.end(), name.begin(), ::tolower);

				if (name == "index") {
					int nIndex=0;
					iss >> nIndex;

					pEle->SetAttribute("index", nIndex);
				}

				else if (name == "class") {
					std::string itemclass;
					std::string itemsubclass;
					iss >> itemclass >> itemsubclass;
					pEle->SetAttribute("class", itemclass.c_str());
					pEle->SetAttribute("subclass", itemsubclass.c_str());
				}

				else if (name == "level") {
					int nLevel=0;
					iss >> nLevel;
					pEle->SetAttribute("level", nLevel);
				}

				else if (name == "wear") {
					int nWear=0;
					iss >> nWear;
					pEle->SetAttribute("wear", nWear);
				}

				else if (name == "limit") {
					std::string limitclass;
					int nLevel=0;
					iss >> limitclass >> nLevel;
					pEle->SetAttribute("reqclass", limitclass.c_str());
					pEle->SetAttribute("reqlevel", nLevel);
				}

				else if (name == "range") {
					int nRange;
					iss >> nRange;
					pEle->SetAttribute("range", nRange);
				}

				else if (name == "buy") {
					int nBuy;
					iss >> nBuy;
					pEle->SetAttribute("buy", nBuy);
				}

				else if (name == "sell") {
					int nSell;
					iss >> nSell;
					pEle->SetAttribute("sell", nSell);
				}

				else if (name == "endurance") {
					int n;
					iss >> n;
					pEle->SetAttribute("endurance", n);
				}

				else if (name == "plural") {
					int n;
					iss >> n;
					pEle->SetAttribute("plural", n);
				}

				else if (name == "use") {
					int n;
					iss >> n;
					pEle->SetAttribute("use", n);
				}

				else if (name == "cooltime") {
					int n;
					iss >> n;
					pEle->SetAttribute("cooltime", n);
				}

				else if (name == "effect") {
					int n;
					iss >> n;
					pEle->SetAttribute("effect", n);
				}

				else if (name == "specialty") {
					XMLElement *pSpecList = doc.NewElement("specialty")->ToElement();

					for (auto& spec: prop->children)
					{
						std::istringstream d(spec->data);
						std::string specname;
						d >> specname;

						XMLElement *pSpec = doc.NewElement(specname.c_str())->ToElement();

						if (specname == "refresh") {
							std::string refreshprop;
							int nvalue;
							d >> refreshprop >> nvalue;

							pSpec->SetAttribute("property", refreshprop.c_str());
							pSpec->SetAttribute("amount", nvalue);
						}

						else if (specname == "buff") {
							int id=0, time=0, value=0;
							d >> id >> time >> value;

							pSpec->SetAttribute("id", id);
							pSpec->SetAttribute("time", time);
							pSpec->SetAttribute("value", value);
						}

						pSpecList->InsertEndChild(pSpec);
					}

					pEle->InsertEndChild(pSpecList);
				}
			}

			pRoot->InsertEndChild(pEle);
		}

		doc.SaveFile(outputPath);
		printf("Converting succeeded.\n");
	}

	void InitMonsterToXML(const char* outputPath)
	{
		FILE *fp = fopen(outputPath, "w+");
		if (!fp) {
			printf("Cannot create %s.\n", outputPath);
			return;
		}

		fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><monsterlist></monsterlist>");
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


		for (auto& monster: root->children)
		{
			XMLElement *pEle = doc.NewElement("monster")->ToElement();

			for (auto& prop: monster->children)
			{
				std::istringstream iss(prop->data);
				std::string name;

				iss >> name;


				std::transform(name.begin(), name.end(), name.begin(), ::tolower);

				if (name == "index") {
					int n=0;
					iss >> n;

					pEle->SetAttribute("index", n);
				}
				else if (name == "race") {
					int n=0;
					iss >> n;

					pEle->SetAttribute("race", n);
				}
				else if (name == "level") {
					int n=0;
					iss >> n;

					pEle->SetAttribute("level", n);
				}
				else if (name == "ai") {
					int n=0;
					iss >> n;

					pEle->SetAttribute("ai", n);
				}
				else if (name == "range") {
					int n=0;
					iss >> n;

					pEle->SetAttribute("range", n);
				}
				else if (name == "sight") {
					int n=0;
					iss >> n;
					pEle->SetAttribute("closesight", n);
					iss >> n;
					pEle->SetAttribute("farsight", n);
				}
				else if (name == "mspeed") {
					int n=0;
					iss >> n;
					pEle->SetAttribute("walkspeed", n);
					iss >> n;
					pEle->SetAttribute("runspeed", n);
				}
				else if (name == "exp") {
					int64_t n=0;
					iss >> n;
					pEle->SetAttribute("exp", n);
				}
			}

			pRoot->InsertEndChild(pEle);
		}

		doc.SaveFile(outputPath);
		printf("Converting succeeded.\n");
	}
};

int main(int argc, char** argv)
{
	if (argc < 4) {
		printf("Bad argumentlist. ([type] [input] [output])\nExample: ./%s InitNPC InitNPC.txt InitNPC.xml\n", argv[0]);
		return 1;
	}

	Document doc;

	if (!doc.LoadFile(argv[2])){
		printf("Cannot open %s.\n", argv[2]);
		return 1;
	}

	printf("Loading completed.\n");

	doc.Parse();

	printf("Parsing completed.\n");

	if (!strcmp(argv[1], "InitNPC"))
		doc.InitNPCToXML(argv[3]);
	else if (!strcmp(argv[1], "InitItem"))
		doc.InitItemToXML(argv[3]);
	else if (!strcmp(argv[1], "InitMonster"))
		doc.InitMonsterToXML(argv[3]);
	else
		printf("%s is not available.\n", argv[1]);

	return 0;
}