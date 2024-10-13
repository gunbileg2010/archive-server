document.getElementById('upload-btn').onclick = function() {
    const fileInput = document.getElementById('file-upload');
    const file = fileInput.files[0];

    const formData = new FormData();
    formData.append('file', file);

    fetch('/upload', {
        method: 'POST',
        body: formData
    })
    .then(response => {
        if (response.ok) {
            alert("File uploaded successfully!");
        } else {
            alert("Error uploading file.");
        }
    });
};

function loadUsers() {
    fetch('/admin/users')
        .then(response => response.json())
        .then(data => {
            const userList = document.getElementById('user-list');
            userList.innerHTML = '';
            for (const [id, username] of Object.entries(data)) {
                const userDiv = document.createElement('div');
                userDiv.innerHTML = `${username} 
                    <select id="clearance-${id}">
                        <option value="Guest">Guest</option>
                        <option value="Delta">Delta</option>
                        <option value="Beta">Beta</option>
                        <option value="Alice">Alice</option>
                    </select>
                    <button onclick="updateClearance(${id})">Change Clearance</button>`;
                userList.appendChild(userDiv);
            }
        });
}

function updateClearance(userId) {
    const newClearance = document.getElementById(`clearance-${userId}`).value;

    fetch(`/admin/user/${userId}`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ clearance_level: newClearance })
    })
    .then(response => {
        if (response.ok) {
            alert("User clearance level updated successfully!");
            loadUsers();  // Refresh the user list
        } else {
            alert("Error updating user clearance level.");
        }
    });
}

// Load users when the page is ready
document.addEventListener('DOMContentLoaded', loadUsers);