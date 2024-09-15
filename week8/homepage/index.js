const wrapper = document.getElementById("contact")
const form = document.getElementById("form");

// Store the original form HTML
const originalFormHTML = wrapper.innerHTML;

const showSuccessMessage = () => {
    wrapper.innerHTML = `
        <div class="submitted-successfully">
            <img src="../assets/icon-success.svg" alt="">
            <h2>Thank You!</h2>
            <p>Your message has been successfully sent. I appreciate you feedback.</p>
            <button class='my_btn' id="dismiss-btn">Back</button>
        </div>
    `;

    // Add event listener to dismiss the message
    document.getElementById('dismiss-btn').addEventListener('click', () => {
        wrapper.innerHTML = originalFormHTML;
        // Re-add the event listener to the reloaded send button
        document.getElementById("form").addEventListener("submit", handleFormSubmit);
    });
};

const handleFormSubmit = (event) => {
    event.preventDefault(); // Prevent form submission refresh
    showSuccessMessage();
};

// Initialize event listener
form.addEventListener("submit", handleFormSubmit);
