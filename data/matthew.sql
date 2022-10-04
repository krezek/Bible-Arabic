DROP TABLE IF EXISTS matthew;
CREATE VIRTUAL TABLE matthew USING FTS5(chapter, verse, prefix, suffix, body);


INSERT INTO matthew (chapter, verse, prefix, suffix, body)
VALUES (1, 1, NULL, NULL, "كِتَابُ مِيلاَدِ يَسُوعَ الْمَسِيحِ ابْنِ دَاوُدَ ابْنِ إِبْراهِيمَ:");

INSERT INTO matthew (chapter, verse, prefix, suffix, body)
VALUES (1, 2, NULL, NULL, "إِبْراهِيمُ وَلَدَ إِسْحاقَ. وَإِسْحاقُ وَلَدَ يَعْقُوبَ. وَيَعْقُوبُ وَلَدَ يَهُوذَا وَإِخْوَتَهُ.");

INSERT INTO matthew (chapter, verse, prefix, suffix, body)
VALUES (1, 3, NULL, NULL, "وَيَهُوذَا وَلَدَ فَارِصَ وَزَارَحَ مِنْ ثَامَارَ. وَفَارِصُ وَلَدَ حَصْرُونَ. وَحَصْرُونُ وَلَدَ أَرَامَ.");
