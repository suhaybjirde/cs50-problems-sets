SELECT name, birth FROM movies, stars, people
WHERE movies.id = stars.movie_id
AND stars.person_id = people.id
AND year = 2004
GROUP BY name
ORDER BY birth;
