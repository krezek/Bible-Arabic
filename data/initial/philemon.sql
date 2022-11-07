DROP TABLE IF EXISTS philemon;
CREATE VIRTUAL TABLE philemon USING FTS5(chapter, verse, prefix, suffix, body);

.read philemon/philemon_1.sql
