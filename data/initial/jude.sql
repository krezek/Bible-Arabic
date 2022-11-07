DROP TABLE IF EXISTS jude;
CREATE VIRTUAL TABLE jude USING FTS5(chapter, verse, prefix, suffix, body);

.read jude/jude_1.sql
