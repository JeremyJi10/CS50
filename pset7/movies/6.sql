SELECT AVG(rating) AS avg_rating
FROM ratings
WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);

/* write a SQL query to determine the average rating of all movies released in 2012.
Your query should output a table with a single column and a single row (plus optional header) containing the average rating. */