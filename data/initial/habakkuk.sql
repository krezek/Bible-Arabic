DROP TABLE IF EXISTS habakkuk;
CREATE VIRTUAL TABLE habakkuk USING FTS5(chapter, verse, prefix, suffix, body);

.read habakkuk/habakkuk_1.sql
.read habakkuk/habakkuk_2.sql
.read habakkuk/habakkuk_3.sql
