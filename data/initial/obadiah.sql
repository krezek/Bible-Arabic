DROP TABLE IF EXISTS obadiah;
CREATE VIRTUAL TABLE obadiah USING FTS5(chapter, verse, prefix, suffix, body);

.read obadiah/obadiah_1.sql
