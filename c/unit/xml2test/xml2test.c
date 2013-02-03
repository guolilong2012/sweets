#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>

int main(int argc, char *argv[])
{
	xmlDocPtr doc;
	xmlNodePtr curNode;
	xmlChar *szKey;
	char *szDocName;

	szDocName = argv[1];
	doc = xmlParseFile(szDocName);
	if (doc == NULL) {
		fprintf(stderr, "Document not parsed sucessfully!\n");
		exit(1);
	}

	curNode = xmlDocGetRootElement(doc);
	if (curNode == NULL) {
		fprintf(stderr, "Empty document!\n");
		xmlFreeDoc(doc);
		exit(1);
	}

	if (xmlStrcmp(curNode->name, (const xmlChar *)"config")) {
		fprintf(stderr, "Document of the wrong type, root node != \"config\"");
		xmlFreeDoc(doc);
	}

	curNode = curNode->xmlChildrenNode;
	while (curNode != NULL) {
		if (!(xmlStrcmp(curNode->name, (const char *)"file"))) {
			szKey = xmlNodeGetContent(curNode);
			printf("file: %s\n",szKey);
			xmlFree(szKey);
		}
		curNode = curNode->next;
	}

	xmlFreeDoc(doc);

	return 0;
}
