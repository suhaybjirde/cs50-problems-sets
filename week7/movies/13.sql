SELECT COUNT(name) FROM movies, stars, people
WHERE movies.id = stars.movie_id
AND people.id = stars.person_id
AND movies.id IN (
    SELECT movies.id FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
    AND (people.name = 'Kevin Bacon' and people.birth = 1958)
)
AND people.name != 'Kevin Bacon';