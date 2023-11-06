#include <db/IndexPredicate.h>

using namespace db;

IndexPredicate::IndexPredicate(Op op, const Field *fvalue) {
    // TODO pa2.2: implement
}

const Field *IndexPredicate::getField() const {
    // TODO pa2.2: implement
    return fieldValue;
}

Op IndexPredicate::getOp() const {
    // TODO pa2.2: implement
    return op;
}

bool IndexPredicate::operator==(const IndexPredicate &other) const {
    // TODO pa2.2: implement
    return (op == other.op) && fieldValue->compare(Op::EQUALS, other.fieldValue);
}

std::size_t std::hash<IndexPredicate>::operator()(const IndexPredicate &ipd) const {
    // TODO pa2.2: implement
    return std::hash<int>()(static_cast<int>(ipd.getOp())) ^ std::hash<std::string>()(ipd.getField()->to_string());

}
