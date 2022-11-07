DROP TABLE IF EXISTS zephaniah;
CREATE VIRTUAL TABLE zephaniah USING FTS5(chapter, verse, prefix, suffix, body);

.read zephaniah/zephaniah_1.sql
.read zephaniah/zephaniah_2.sql
.read zephaniah/zephaniah_3.sql
