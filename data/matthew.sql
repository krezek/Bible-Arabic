DROP TABLE IF EXISTS matthew;
CREATE VIRTUAL TABLE matthew USING FTS5(chapter, verse, prefix, suffix, body);


INSERT INTO matthew (chapter, verse, prefix, suffix, body)
VALUES (1, 1, NULL, NULL, "كِتَابُ مِيلاَدِ يَسُوعَ الْمَسِيحِ ابْنِ دَاوُدَ ابْنِ إِبْراهِيمَ:");

INSERT INTO matthew (chapter, verse, prefix, suffix, body)
VALUES (1, 2, NULL, char(10) || char(10), "إِبْراهِيمُ وَلَدَ إِسْحاقَ. وَإِسْحاقُ وَلَدَ يَعْقُوبَ. وَيَعْقُوبُ وَلَدَ يَهُوذَا وَإِخْوَتَهُ.");

INSERT INTO matthew (chapter, verse, prefix, suffix, body)
VALUES (1, 3, NULL, NULL, "وَيَهُوذَا وَلَدَ فَارِصَ وَزَارَحَ مِنْ ثَامَارَ. وَفَارِصُ وَلَدَ حَصْرُونَ. وَحَصْرُونُ وَلَدَ أَرَامَ.");



INSERT INTO matthew (chapter, verse, prefix, suffix, body)
VALUES (2, 1, NULL, NULL, "وَلَمَّا وُلِدَ يَسُوعُ فِي بَيْتِ لَحْمِ الْيَهُودِيَّةِ، فِي أَيَّامِ هِيرُودُسَ الْمَلِكِ، إِذَا مَجُوسٌ مِنَ الْمَشْرِقِ قَدْ جَاءُوا إِلَى أُورُشَلِيمَ");

INSERT INTO matthew (chapter, verse, prefix, suffix, body)
VALUES (2, 2, NULL, NULL, "قَائِلِينَ: «أَيْنَ هُوَ الْمَوْلُودُ مَلِكُ الْيَهُودِ؟ فَإِنَّنَا رَأَيْنَا نَجْمَهُ فِي الْمَشْرِقِ وَأَتَيْنَا لِنَسْجُدَ لَهُ».");

INSERT INTO matthew (chapter, verse, prefix, suffix, body)
VALUES (2, 3, NULL, NULL, "فَلَمَّا سَمِعَ هِيرُودُسُ الْمَلِكُ اضْطَرَبَ وَجَمِيعُ أُورُشَلِيمَ مَعَهُ.");
