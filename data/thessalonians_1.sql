DROP TABLE IF EXISTS thessalonians_1;
CREATE VIRTUAL TABLE thessalonians_1 USING FTS5(chapter, verse, prefix, suffix, body);

.read thessalonians_1/thessalonians_1_1.sql
.read thessalonians_1/thessalonians_1_2.sql
.read thessalonians_1/thessalonians_1_3.sql
.read thessalonians_1/thessalonians_1_4.sql
.read thessalonians_1/thessalonians_1_5.sql
