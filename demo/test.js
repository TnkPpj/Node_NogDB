// const nogdb = require('./build/Debug/nogdb');
// const Class = new nogdb.Class();
// const Property = new nogdb.Property();
// const Vertex = new nogdb.Vertex();
// const Edge = new nogdb.Edge();
// const Db = new nogdb.Db();
// const Traverse = new nogdb.Traverse();

// let classFilter = new nogdb.ClassFilter(["1","2","3"]);
// classFilter.getClassName();
// console.log(classFilter.size());
// classFilter.add("4");
// let classNames = classFilter.getClassName();
// console.log(classNames);
// console.log(classFilter.size());
// classFilter.remove("1");
// classNames = classFilter.getClassName();
// console.log(classNames);
// console.log(classFilter.size());
// console.log(classFilter.empty());
// classFilter.remove("2");
// classFilter.remove("3");
// classFilter.remove("4");
// console.log(classFilter.empty());
// classFilter.add("4");
// classFilter.add("4");
// classFilter.add("4");
// console.log(classFilter.size());

const nogdb = require('./build/Debug/nogdb');
let ctx = new nogdb.Context("test.db");

// console.log(ctx.getMaxVersionId() + "---" + ctx.getMaxTxnId());
let txn = new nogdb.Txn(ctx,"READ_WRITE");
// // console.log(ctx.getMaxVersionId() + "---" + ctx.getMaxTxnId());
// nogdb.createClass(txn,"files","VERTEX");
// console.log(ctx.getMaxVersionId() + "---" + ctx.getMaxTxnId());
txn.commit();