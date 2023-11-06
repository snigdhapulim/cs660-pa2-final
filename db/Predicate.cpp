#include <db/Predicate.h>

using namespace db;

// TODO pa2.2: implement
Predicate::Predicate(int field, Op op, const Field *operand) {}

int Predicate::getField() const {
    // TODO pa2.2: implement
    return fieldNum;
}

Op Predicate::getOp() const {
    // TODO pa2.2: implement
    return op;
}

const Field *Predicate::getOperand() const {
    // TODO pa2.2: implement
    return operand;
}

bool Predicate::filter(const Tuple &t) const {
    // TODO pa2.2: implement
    if (t.getTupleDesc().numFields() <= fieldNum) {
        // Handle error: fieldNum is out of bounds for the tuple
        return false;
    }

    const db::Field& field = t.getField(fieldNum);
    return field.compare(op, operand);
}
