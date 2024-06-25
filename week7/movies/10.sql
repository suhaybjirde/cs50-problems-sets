SELECT name FROM movies, ratings, people, directors
WHERE movies.id = ratings.movie_id
AND movies.id = directors.movie_id
AND people.id = directors.person_id
AND rating >= 9.0
GROUP BY name;