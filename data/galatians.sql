DROP TABLE IF EXISTS galatians;
CREATE VIRTUAL TABLE galatians USING FTS5(chapter, verse, prefix, suffix, body);

.read galatians/galatians_1.sql
.read galatians/galatians_2.sql
.read galatians/galatians_3.sql
.read galatians/galatians_4.sql
.read galatians/galatians_5.sql
.read galatians/galatians_6.sql
