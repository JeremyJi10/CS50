SELECT title
FROM movies JOIN stars ON movies.id = stars.movie_id
WHERE person_id IN (SELECT id FROM people WHERE name = 'Johnny Depp') OR person_id IN (SELECT id FROM people WHERE name = 'Helena Bonham Carter')
GROUP BY title
HAVING COUNT(title) = 2;

/* write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
Your query should output a table with a single column for the title of each movie.
You may assume that there is only one person in the database with the name Johnny Depp.
You may assume that there is only one person in the database with the name Helena Bonham Carter. */