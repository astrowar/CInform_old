#include "BlockInterpreter.h"
#include  "QueryStack.h"

 

 

void QueryStack::addQuery(HBlock b1, HBlock b2) {
    items.push_back(QueryItem(b1, b2));
}

bool QueryStack::isQuery(HBlock b1, HBlock b2) {
    for (auto &q : items) {
        if ((q.b1 == b1) && (q.b2 == b2)) return true;
    }
    return false;
}