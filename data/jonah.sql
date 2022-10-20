DROP TABLE IF EXISTS jonah;
CREATE VIRTUAL TABLE jonah USING FTS5(chapter, verse, prefix, suffix, body);

.read jonah/jonah_1.sql
.read jonah/jonah_2.sql
.read jonah/jonah_3.sql
.read jonah/jonah_4.sql
